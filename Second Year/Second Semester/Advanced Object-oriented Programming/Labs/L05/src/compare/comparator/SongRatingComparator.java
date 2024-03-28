package compare.comparator;

import java.util.Comparator;

public class SongRatingComparator implements Comparator<Song> {
    @Override
    public int compare(Song song1, Song song2) {
        return Double.compare(song1.getRating(), song2.getRating());
    }

}
