package compare.comparator;

import java.util.Comparator;

public class SongNameComparator implements Comparator<Song> {

    @Override
    public int compare(Song song1, Song song2) {
        return song1.getName().compareToIgnoreCase(song2.getName());
    }
}
