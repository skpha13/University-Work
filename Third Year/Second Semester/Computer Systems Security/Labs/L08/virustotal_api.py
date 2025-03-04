import hashlib
import json
import os
from typing import Any

import requests
from dotenv import load_dotenv


def compute_sha256(file_path: str) -> str:
    with open(file_path, "rb") as f:
        readable_hash = hashlib.sha256(f.read()).hexdigest()

    return readable_hash


def get_file_info(file_path: str) -> Any:
    api_url = "https://www.virustotal.com/api/v3/files"
    headers = {"x-apikey": os.getenv("API_KEY")}

    with open(file_path, "rb") as file:
        files = {"file": ("malware.png", file)}
        response = requests.post(api_url, headers=headers, files=files)

        if response.status_code == 200:
            file_identifier = compute_sha256(file_path)
            url = f"https://www.virustotal.com/api/v3/files/{file_identifier}"

            response2 = requests.request("GET", url, headers=headers)

            if response2.status_code == 200:
                return response2.json()

    return None


def main():
    load_dotenv()

    result = get_file_info("./buffer_overflow.cpp")
    print(json.dumps(result, indent=4))


if __name__ == "__main__":
    main()
