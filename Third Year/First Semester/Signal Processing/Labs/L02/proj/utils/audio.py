import os
from io import TextIOWrapper

import scipy.io.wavfile as wav
import sounddevice
from numpy import ndarray

# create folder if it does not exist
os.makedirs(f"{os.getcwd()}/wavs", exist_ok=True)


class Audio:
    """A wrapper class used to handle audio-related operations such as saving and playing audio files.

    Attributes:
        BASE_OUTPUT_FOLDER (str): The default folder where audio files are saved.
    """

    BASE_OUTPUT_FOLDER = "wavs"

    @staticmethod
    def get_path(filename: str):
        return os.path.join(os.getcwd(), Audio.BASE_OUTPUT_FOLDER, filename)

    @staticmethod
    def write(filename: str, data: ndarray, rate: int = 44100) -> None:
        """Writes an audio file to the specified location.

        Args:
            filename (str | TextIOWrapper): The name of the file or file object where the audio will be saved.
            rate (int): The sample rate (in samples per second) for the audio data.
            data (ndarray): The audio data in NumPy array format to be written to the file.
        """
        wav.write(Audio.get_path(filename), rate, data)

    @staticmethod
    def play(filename: str, loop: bool = False, duration: int | None = None) -> None:
        """Plays an audio file from the specified location.

        Args:
            filename (str): The name of the file to be played from the BASE_OUTPUT_FOLDER.
            loop (bool, optional): If True, the audio will loop continuously. Defaults to False.
            duration (float, optional): Duration (in milliseconds) to play the audio. If None, plays until the end of the file.
        """
        file_rate, audio_file = wav.read(Audio.get_path(filename))
        sounddevice.play(audio_file, samplerate=file_rate, loop=loop)

        if duration is not None:
            sounddevice.sleep(duration)

        sounddevice.stop()
