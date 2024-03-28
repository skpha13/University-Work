package compare.comparator;

import java.util.Comparator;

public class SongYearComparator implements Comparator<Song> {
    @Override
    public int compare(Song o1, Song o2) {
        return Integer.compare(o1.getYear(), o2.getYear());
    }
}
