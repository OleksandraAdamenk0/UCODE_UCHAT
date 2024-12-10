DROP TRIGGER IF EXISTS update_last_message;
DROP TRIGGER IF EXISTS delete_messages_on_chat_delete;

-- table chats
CREATE TABLE IF NOT EXISTS chats (
                                     chat_id INTEGER PRIMARY KEY,
                                     chat_name TEXT NOT NULL,
                                     last_message TEXT,
                                     photo BLOB
);

-- table messages
CREATE TABLE IF NOT EXISTS messages (
                                        id INTEGER PRIMARY KEY,
                                        chat_id INTEGER NOT NULL,
                                        sender TEXT NOT NULL,
                                        reply_to_id INTEGER,
                                        timestamp DATETIME NOT NULL,
                                        binary BLOB,
                                        message TEXT,
                                        FOREIGN KEY(chat_id) REFERENCES chats(chat_id),
    FOREIGN KEY(reply_to_id) REFERENCES messages(id)
);


-- table contacts
CREATE TABLE IF NOT EXISTS contacts (
                                        id INTEGER PRIMARY KEY,
                                        username TEXT NOT NULL,
                                        photo BLOB
);

-- table settings
CREATE TABLE IF NOT EXISTS settings (
                                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                                        email TEXT,
                                        phone TEXT,
                                        photo BLOB,
                                        theme TEXT
);

-- triggers
CREATE TRIGGER update_last_message
    AFTER INSERT ON messages
    FOR EACH ROW
BEGIN
    UPDATE chats
    SET last_message = NEW.message
    WHERE chat_id = NEW.chat_id;
END;

CREATE TRIGGER delete_messages_on_chat_delete
    AFTER DELETE ON chats
    FOR EACH ROW
BEGIN
    DELETE FROM messages WHERE chat_id = OLD.chat_id;
END;