with open("message.txt", "r") as file:
    message = file.read()

letters_by_frequency = ["E", "A", "T", "O", "N", "I", "R", "S", "C", "H", "D", "L", "U", "P", "B", "M", "Y", "G", "V", "W", "F", "J", "K", "X", "Q", "Z"]
message_letter_frequencies: dict[str, int] = {}

for character in message:
    if not character.isalpha():
        continue

    message_letter_frequencies.setdefault(character, 0)
    message_letter_frequencies[character] += 1

print(sorted(message_letter_frequencies.items(), key=lambda item: (-item[1], item[0])))
sorted_message_frequencies = [key for key, _ in sorted(message_letter_frequencies.items(), key=lambda item: (-item[1], item[0]))]

print(sorted_message_frequencies)
print(letters_by_frequency)

result = ""
for character in message:
    if character.isalpha():
        index = sorted_message_frequencies.index(character)
        result += letters_by_frequency[index]
    else:
        result += character

print(result)
