# Lab 7

## 1

- A - T
- B - F
- C - T
- D - T
- E - F
- F - F
- G - F

Used this [tool](https://10015.io/tools/md5-encrypt-decrypt) -> parola123

## 3

### 1

Someone who has access to the code can see the `secretKey`.
Passwords are stored plain text in the database.

### 2

Usernames do not need to be hashed.
This means that multiple people with the same username can coexist and also make the process of user lookups more inefficient.

### 3

No salting.
SHA256 is usually not recommended for password hashing.

### 4

Salt should be generated random for each hash. Not used globally.
 
### 5

MD5 is not good for password hashing.