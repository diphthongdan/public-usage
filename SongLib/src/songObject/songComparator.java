package songObject;

import java.util.Comparator;

public class songComparator implements Comparator<song> {
	@Override
	//Compares song s1 to song s2
	public int compare(song s1,song s2) {
		int x=s1.getTitle().compareToIgnoreCase(s2.getTitle());
		//If titles are the same, check artist ordering
		if(x==0) {
			int y=s1.getArtist().compareToIgnoreCase(s2.getArtist());
			if(y==0) {
				return y;
			}
			return y;
		}
		return x;
	}

}
