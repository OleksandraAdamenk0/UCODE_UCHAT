DROP TRIGGER IF EXISTS delete_user_from_chats_users;
DROP TRIGGER IF EXISTS delete_chat_from_chats_users;
DROP TRIGGER IF EXISTS sync_settings_on_insert;
DROP TRIGGER IF EXISTS sync_settings_on_update;
DROP TRIGGER IF EXISTS sync_settings_on_delete;

CREATE TABLE IF NOT EXISTS users (
                                     id INTEGER PRIMARY KEY AUTOINCREMENT,
                                     username TEXT NOT NULL UNIQUE,
                                     password TEXT NOT NULL,
                                     email TEXT UNIQUE,
                                     phone TEXT UNIQUE,
                                     photo BLOB
);

CREATE TABLE IF NOT EXISTS chats (
                                     id INTEGER PRIMARY KEY AUTOINCREMENT,
                                     chat_name TEXT NOT NULL,
                                     photo BLOB
);

CREATE TABLE IF NOT EXISTS messages (
                                     id INTEGER PRIMARY KEY AUTOINCREMENT,
                                     chat_id INTEGER NOT NULL,
                                     sender_id INTEGER NOT NULL,
                                     reply_to_id INTEGER,
                                     timestamp DATETIME NOT NULL,
                                     binary BLOB,
                                     message TEXT,
                                     FOREIGN KEY(chat_id) REFERENCES chats(id),
                                     FOREIGN KEY(sender_id) REFERENCES users(id),
                                     FOREIGN KEY(reply_to_id) REFERENCES messages(id)
);

CREATE TABLE IF NOT EXISTS chats_users (
                                         chat_id INTEGER NOT NULL,
                                         user_id INTEGER NOT NULL,
                                         FOREIGN KEY(chat_id) REFERENCES chats(id),
                                         FOREIGN KEY(user_id) REFERENCES users(id),
                                         UNIQUE(chat_id, user_id)
);

CREATE TRIGGER delete_user_from_chats_users
    AFTER DELETE ON users
    FOR EACH ROW
BEGIN
    DELETE FROM chats_users WHERE user_id = OLD.id;
END;

CREATE TRIGGER delete_chat_from_chats_users
    AFTER DELETE ON chats
    FOR EACH ROW
BEGIN
    DELETE FROM chats_users WHERE chat_id = OLD.id;
END;

CREATE TABLE IF NOT EXISTS settings (
                                     id INTEGER NOT NULL,
                                     email TEXT,
                                     phone TEXT,
                                     photo BLOB,
                                     theme TEXT,
                                     FOREIGN KEY(id) REFERENCES users(id)
);

CREATE TRIGGER sync_settings_on_insert
    AFTER INSERT ON users
    FOR EACH ROW
BEGIN
    INSERT INTO settings (id, email, phone, photo)
    VALUES (NEW.id, NEW.email, NEW.phone, NEW.photo);
END;

CREATE TRIGGER sync_settings_on_update
    AFTER UPDATE ON users
    FOR EACH ROW
BEGIN
    UPDATE settings
    SET email = NEW.email,
        phone = NEW.phone,
        photo = NEW.photo
    WHERE id = NEW.id;
END;

CREATE TRIGGER sync_settings_on_delete
    AFTER DELETE ON users
    FOR EACH ROW
BEGIN
    DELETE FROM settings WHERE id = OLD.id;
END;
