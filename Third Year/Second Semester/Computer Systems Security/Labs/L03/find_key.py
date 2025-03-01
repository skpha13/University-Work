import base64

from typing import Tuple

message_b64 = "o9/khC3Pf3/9CyNCbdzHPy5oorccEawZSFt3mgCicRnihDSM8Obhlp3vviAVuBbiOtCSz6husBWqhfF0Q/8EZ+6iI9KygD3hAfFgnzyv9w=="
message_bytes = base64.b64decode(message_b64)
message_binary = "".join(format(byte, "08b") for byte in message_bytes)

key_hex = "ecb181a479a6121add5b42264db9b44b4b48d7d93c62c56a3c3e1aba64c7517a90ed44f8919484b6ed8acc4670db62c249b9f5bada4ed474c9e4d111308b614788cd4fbdc1e949c1629e12fa5fdbd9"
key_bytes = bytes.fromhex(key_hex)
key_binary = bin(int(key_hex, 16))[2:].zfill(len(key_hex) * 4)

def xor(message_bytes: bytes, key_bytes: bytes) -> Tuple[bytes, str, str]:
    result_bytes = bytes([message_byte ^ key_byte for message_byte, key_byte in zip(message_bytes, key_bytes)])
    result_ascii = result_bytes.decode("ascii")
    result_string = "".join(chr(byte) for byte in result_bytes)

    return result_bytes, result_ascii, result_string

_, _, xor_result_string = xor(message_bytes, key_bytes)

print(f"1. Decrypted Message: {xor_result_string}")

desired_message = "Orice text clar poate obtinut dintr-un text criptat cu OTP dar cu alta cheie..."
desired_message_bytes = desired_message.encode("utf-8")

desired_key_bytes = bytes([m ^ d for m, d in zip(message_bytes, desired_message_bytes)])
desired_key_binary = ''.join(f'{byte:08b}' for byte in desired_key_bytes)
binary_data = int(desired_key_binary, 2).to_bytes((len(desired_key_binary) + 7) // 8, byteorder='big')
desired_key_hexadecimal = binary_data.hex()

print(f"2. Key Hexadecimal: {desired_key_hexadecimal}")

xor_result_bytes, _, xor_result_string = xor(message_bytes, desired_key_bytes)
print(f"2. Decrypted Message: {xor_result_string}")
