# Server API

## Account Registration

**Description**: A request to create a new user account. 
The server will verify that the username is unique, 
the password meets security requirements, 
and that the email or phone number is formatted correctly. 
Upon successful registration, the server will issue an access token 
and a refresh token.

**Request Data**

The client sends a JSON object with the following fields:

|   Field    |    Type    |	 Required  | Description |
| ---------- | ---------- | ---------- | ----------- |
| action     |	string	  | yes        | Specifies the action type; for registration, use "register" |
| username   |	string    |	yes	       | Unique username for the user |
| password   |	string    |	yes        | Password that meets the application's security criteria |
| email      |	string    |	no         | User's email address |
| phone      |	string    |	no	       | User's phone number in international format |

Note: either email or phone should be sent

### Sample Request:

```json
{
"action": "register",
"username": "new_user",
"password": "SecurePass123!",
"email": "user@example.com",
"phone": "+1234567890"
}
```

### Server Responses

**Successful Response:**

```json
{
  "status": "0",
  "message": "Account created successfully.",
  "tokens": {
    "access_token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
    "refresh_token": "dGhpc0lzVGhlUmVmcmVzaFRva2VuMTIzNDU2..."
  }
}
```

**Error Responses:**

If no username was provided:

```json
{
"status": "-1",
"message": "Empty Username field."
}
```

If username is already taken:

```json
{
"status": "-2",
"message": "Username already taken."
}
```

If password does not meet security requirements:

Password must meet the following requirements:
- At least 8 characters
- At least one uppercase letter
- At least one lowercase letter
- At least one digit 
- At least one of the following special characters: !@#$*-_?.
- Only these special characters are allowed: !@#$*-_?.

If phone number is already registered:

```json
{
  "status": "-3",
  "message": "Password doesn't meet requirements."
}
```

If no Phone number and no Email was provided:

```json
{
"status": "-4",
"message": "Either a phone number or an email has to be provided."
}
```

If Phone number has an invalid format:

```json
{
"status": "-5",
"message": "Invalid phone format."
}
```

If Email has an invalid format:

```json
{
"status": "-6",
"message": "Invalid email format."
}
```

If email is already registered:

```json
{
"status": "-7",
"message": "Email is already registered."
}
```

If phone number is already registered:

```json
{
"status": "-8",
"message": "Phone number is already registered."
}
```

If there is a server error while processing the request:

``` json
{
"status": "-9",
"message": "Internal server error. Please try again later."
}
```

## User Login

**Description**: A request to authenticate an existing user using their username and password. Upon successful authentication, the server will issue an access token and a refresh token.

**Request Data**

The client sends a JSON object with the following fields:

|   Field    |    Type    |	 Required  | Description |
| ---------- | ---------- | ---------- | ----------- |
| action     |	string	  | yes        | Specifies the action type; for login, use "login" |
| username   |	string    |	yes	       | The username of the user |
| password   |	string    |	yes        | The password of the user |

### Sample Request:

``` json
{
"action": "login",
"username": "existing_user",
"password": "UserSecurePass123!"
}
``` 

### Server Responses

**Successful Response:**

```  json
{
"status": "0",
"message": "Login successful.",
"tokens": {
"access_token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
"refresh_token": "dGhpc0lzVGhlUmVmcmVzaFRva2VuMTIzNDU2..."
}
}
``` 

**Error Responses:**

If username or password is incorrect:

``` json
{
"status": "-1",
"message": "Invalid username or password."
}
```

If phone number is already registered:

``` json
{
"status": "-2",
"message": "Internal server error. Please try again later."
}
```

## Token Refresh (For the future development)

Description: A request to refresh the access token using the refresh token. This is used to obtain a new access token without requiring the user to log in again.

**Request Data**

|   Field        |    Type    |	 Required  | Description |
| -------------- | ---------- | ---------- | ----------- |
| action         |	string	  | yes        | Specifies the action type; for refreshing tokens, use "refresh_token" |
| refresh_token  |	string    |	yes        | The refresh token issued during login or registration |


**Sample Request:**

```json
{
    "action": "refresh_token",
    "refresh_token": "dGhpc0lzVGhlUmVmcmVzaFRva2VuMTIzNDU2..."
}
```

### Server Responses

**Successful Response:**

```json
{
    "status": "0",
    "message": "Token refreshed successfully.",
    "tokens": {
        "access_token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...",
        "refresh_token": "dGhpc0lzVGhlUmVmcmVzaFRva2VuMTIzNDU2..."
    }
}
```

**Error Responses:**

If the refresh token is invalid or expired:

```json
{
    "status": "-1",
    "message": "Invalid or expired refresh token."
}
``` 

If phone number is already registered:

``` json
{
"status": "-2",
"message": "Internal server error. Please try again later."
}
```

## Get All Contacts

**Description:** A request to retrieve the list of all contacts associated with the authenticated user. 
Each contact will include a unique ID, name, and profile photo URL for display purposes.

### Request Data

The client sends a JSON object with the following fields:

| Field   |    Type    |	 Required  | Description |
|---------| ---------- | ---------- | ----------- |
| action  |	string	  | yes        | Specifies the action type; for fetching contacts, use "get_contacts" |
| user_id |	string	  | yes        | The unique identifier of the user |
| token   |	string    |	yes	       | The access token for authentication |

### Sample Request

```json
{
  "action": "get_contacts",
  "user_id": "12345",
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
``` 

### Server Responses

**Successful Response:**

```json
{
  "status": "0",
  "message": "Contacts retrieved successfully.",
  "count": 2,
  "contacts": [
    {
      "id": "12345",
      "name": "Alice Smith",
      "photo": "https://example.com/photos/alice.jpg"
    },
    {
      "id": "67890",
      "name": "Bob Johnson",
      "photo": "https://example.com/photos/bob.jpg"
    }
  ]
}
``` 

**Error Responses:**

If the user id is missing or invalid:

```  json
{
"status": "-1",
"message": "Invalid or missing user_id."
}

If the token is missing or invalid:

```  json
{
"status": "-2",
"message": "Invalid or missing token."
}
```

If an internal server error occurred:

``` json
{
"status": "-3",
"message": "Internal server error. Please try again later."
}
```

## Get All Chats

**Description:** A request to retrieve the list of all chats for the authenticated user. Each chat will have a unique ID, 
a name (e.g., the name of a group or contact), and a profile photo URL for display.

### Request Data

The client sends a JSON object with the following fields:

| Field   |    Type    |	 Required  | Description |
|---------| ---------- | ---------- | ----------- |
| action  |	string	  | yes        | Specifies the action type; for fetching contacts, use "get_contacts" |
| user_id |	string	  | yes        | The unique identifier of the user |
| token   |	string    |	yes	       | The access token for authentication |

### Sample Request:

```json
{
  "action": "get_chats",
  "user_id": "12345",
  "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
``` 

### Server Responses

**Successful Response:**

``` json 
{
"status": "0",
"message": "Chats retrieved successfully.",
"count": 2,
"chats": [
{
"id": "54321",
"name": "Project Team",
"photo": "https://example.com/photos/project.jpg"
},
{
"id": "98765",
"name": "John Doe",
"photo": "https://example.com/photos/john.jpg"
}
]
}
``` 

**Error Responses:**

If the user id is missing or invalid:

```  json
{
"status": "-1",
"message": "Invalid or missing user_id."
}
```

If the token is missing or invalid:

```  json
{
"status": "-2",
"message": "Invalid or missing token."
}
```

If an internal server error occurred:

``` json
{
"status": "-3",
"message": "Internal server error. Please try again later."
}
```

## Get Settings
**Description**: 

### Request Data

The client sends a JSON object with the following fields:


| Field    |    Type    |	 Required  | Description                                                          |
|----------| ---------- | ---------- |----------------------------------------------------------------------|
| action   |	string	  | yes        | Specifies the action type; for fetching contacts, use "get_settings" |
| username |	string	  | yes        | The unique ID of the user                                            |
| token    |	string    |	yes	       | The access token for authentication                                  |


### Sample Request:

``` json
{
"action": "get_settings",
"username": "@debil",
"token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

### Server Responses

**Successful Response:**

``` json
{
"status": "0",
"message": "Settings retrieved successfully.",
"email": "email@example.com"
"phone": "+000 000 00 00"
"photo": "something encoded "
"photo_size": "1024"
"theme": "theme"
}
```

**Error Responses:**

If the token is missing or invalid:

``` json
{
"status": "-1",
"message": "Invalid or missing token."
}
```

If the user id is missing or invalid:


```  json
{
"status": "-2",
"message": "Invalid or missing user_id."
}
```

If an internal server error occurred:

``` json
{
"status": "-3",
"message": "Internal server error. Please try again later."
}
```



## Get Messages from a Chat


**Description**: A request to fetch all messages from a specific chat. Each message will include a unique ID, 
the chat ID it belongs to, the sender's ID, the message content, and the time of sending.

### Request Data

The client sends a JSON object with the following fields:


| Field   |    Type    |	 Required  | Description                                                  |
|---------| ---------- | ---------- |--------------------------------------------------------------|
| action  |	string	  | yes        | Specifies the action type; for fetching contacts, use "get_messages" |
| chat_id |	string	  | yes        | The unique ID of the chat from which to fetch messages |
| token   |	string    |	yes	       | The access token for authentication                          |

### Sample Request:

``` json
{
"action": "get_messages",
"chat_id": "54321",
"token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9..."
}
```

### Server Responses

**Successful Response:**

``` json
{
"status": "0",
"message": "Messages retrieved successfully.",
"count": 2,
"messages": [
{
"id": "1",
"chat_id": "54321",
"sender_id": "12345",
"content": "Hello everyone!",
"timestamp": "2024-11-12T08:30:00Z"
},
{
"id": "2",
"chat_id": "54321",
"sender_id": "67890",
"content": "Hi Alice, how are you?",
"timestamp": "2024-11-12T08:35:00Z"
}
]
}
```

**Error Responses:**

If the token is missing or invalid:

``` json
{
"status": "-1",
"message": "Invalid or missing token."
}
```

If the chat ID is invalid or not found:

``` json
{
"status": "-2",
"message": "Chat not found."
}
```

If phone number is already registered:

``` json
{
"status": "-3",
"message": "Internal server error. Please try again later."
}
```

## User Profile Request

**Description:** A request to retrieve user profile information. The server will return key profile data, including settings and contact details.

### Request Data

| Field   |    Type    |	 Required  | Description                                                         |
|---------| ---------- | ---------- |---------------------------------------------------------------------|
| action  |	string	  | yes        | Specifies the action type; for fetching contacts, use "get_profile" |
| user_id |	string	  | yes        | The unique identifier of the user             |
| token   |	string    |	yes	       | The access token for authentication                                 |

### Sample Request:

``` json
{
"action": "get_profile",
"user_id": "unique_user_id"
}
```

### Server Responses

**Successful Response:**

``` json
{
"status": "0",
"message": "Profile retrieved successfully.",
"profile": {
"username": "user123",
"phone": "+1234567890",
"email": "user@example.com",
"notifications_enabled": true,
"theme": "light" // Possible values: "light" or "dark"
}
}
```

**Error Responses:**

If the user ID is not found:

``` json
{
"status": "-1",
"message": "User not found."
}
```

If the request is missing required fields:

``` json
{
"status": "-2",
"message": "Missing or invalid request data."
}
```

If there is a server error while retrieving the profile:

``` json
{
"status": "-3",
"message": "Internal server error. Please try again later."
}
```

## Message Sending Request

**Description:** A request to send a message in a specified chat. 
The server processes the message and delivers it to the recipient(s) in the chat.

### Request Data

The client sends a JSON object with the following fields:


| Field     |    Type    |	 Required  | Description                                                         |
|-----------| ---------- | ---------- |---------------------------------------------------------------------|
| action    |	string	  | yes        | Specifies the action type; for fetching contacts, use "send_message" |
| chat_id   |	string	  | yes        | The unique ID of the chat to which the message is being sent             |
| sender_id |	string	  | yes        | The unique ID of the user sending the message           |
| content   |	string	  | yes        | The content of the message            |
| token     |	string    |	yes	       | The access token for authentication                                 |

### Sample Request:

``` json
{
"action": "send_message",
"chat_id": "chat12345",
"sender_id": "user123",
"content": "Hello, how are you?"
}
```

### Server Responses

**Successful Response:**

``` json
{
"status": "0",
"message": "Message sent successfully.",
"message_id": "msg7890",
"timestamp": "2024-11-12T14:45:00Z"
}
```

**Error Responses:**

If the chat ID is invalid or not found:

``` json
{
"status": "-1",
"message": "Chat not found."
}
```

If the sender ID is invalid or does not have permission to send messages in this chat:

``` json
{
"status": "-2",
"message": "Permission denied. Unable to send message."
}
```

If the content is empty or exceeds the allowed length:

``` json
{
"status": "-3",
"message": "Invalid message content."
}
```

If there is a server error while processing the message:

``` json
{
"status": "-4",
"message": "Internal server error. Please try again later."
}
```

# Next to develop

* Add user to the contacts
* Create chat
* Add user to the chat
* Remove user from the chat
* Leave chat
* Delete account
* Update password
* Update login
* Update Email
* Update Phone
* ...


