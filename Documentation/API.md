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

If username is already taken:

```json
{
"status": "-1",
"message": "Username already taken."
}
```

If password does not meet security requirements:

```json
{
"status": "-2",
"message": "Password does not meet security requirements."
}
```

If email or phone number has an invalid format:

```json
{
"status": "-3",
"message": "Invalid email or phone format."
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

If the account is locked or inactive:

``` json
{
"status": "-2",
"message": "Account is locked or inactive."
}
```

## Token Refresh

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


