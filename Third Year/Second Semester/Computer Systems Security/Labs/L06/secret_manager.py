import secrets
import bcrypt

class SecretManager:
    CAPS_LETTERS = "QWERTYUIOPASDFGHJKLZXCVBNM"
    LOWER_LETTERS = CAPS_LETTERS.lower()
    LETTERS = LOWER_LETTERS + CAPS_LETTERS
    NUMBERS = "0123456789"
    SPECIAL_CHARACTERS = ".!$@"
    CHARACTERS = LETTERS + NUMBERS + SPECIAL_CHARACTERS

    @staticmethod
    def generate_password(length: int = 10) -> str:
        """Safe password generation"""

        password = (
                secrets.choice(SecretManager.CAPS_LETTERS) +
                secrets.choice(SecretManager.LOWER_LETTERS) +
                secrets.choice(SecretManager.NUMBERS) +
                secrets.choice(SecretManager.SPECIAL_CHARACTERS)
        )

        for _ in range(length - 4):
            password += secrets.choice(SecretManager.CHARACTERS)

        return password

    @staticmethod
    def token_urlsafe(length: int = 32) -> str:
        """Generate web token like JWT"""
        return secrets.token_urlsafe(length)

    @staticmethod
    def token_hex(length: int = 32) -> str:
        """Generate key to encrypt messages"""
        return secrets.token_hex(length)

    @staticmethod
    def compare(a: str, b: str) -> bool:
        return secrets.compare_digest(a, b)

    @staticmethod
    def generate_binary_key(length: int = 100) -> bytes:
        return secrets.token_bytes(length)

    @staticmethod
    def hash_password(password: str) -> bytes:
        salt = bcrypt.gensalt()
        hashed_password = bcrypt.hashpw(password.encode(), salt)

        return hashed_password

    @staticmethod
    def check_password(password: str, hashed_password: bytes) -> bool:
        return bcrypt.checkpw(password.encode(), hashed_password)


def main():
    print(SecretManager.generate_password())
    print(SecretManager.token_urlsafe())
    print(SecretManager.token_hex())
    print(SecretManager.compare("test", "test"))

    print(SecretManager.generate_binary_key())

    password = "test"
    hashed_password = SecretManager.hash_password(password)
    print(hashed_password)
    print(SecretManager.check_password(password, hashed_password))


if __name__ == '__main__':
    main()