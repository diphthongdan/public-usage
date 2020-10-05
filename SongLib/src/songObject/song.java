package songObject;

public class song implements Comparable<song>{
	private String title;
	private String artist;
	private String album;
	private String year;
	
	public song(String title,String artist,String album,String year) {
		this.setTitle(title);
		this.setArtist(artist);
		this.setAlbum(album);
		this.setYear(year);
	}

	public String getYear() {
		return this.year;
	}

	public void setYear(String year) {
		this.year = year;
	}

	public String getAlbum() {
		return this.album;
	}

	public void setAlbum(String album) {
		this.album = album;
	}

	public String getTitle() {
		return this.title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getArtist() {
		return this.artist;
	}

	public void setArtist(String artist) {
		this.artist = artist;
	}
	/*Case INsensitive song comparator
	 * Returns negative if this song comes before song argument
	 * Returns positive if this song arguments comes after song argument
	 * Returns 0 if songs have same artist and title
	 */
	@Override
	public int compareTo(song o) {
		int x=this.title.compareToIgnoreCase(o.title);
		//If titles are the same, check artist ordering
		if(x==0) {
			int y=this.artist.compareToIgnoreCase(o.artist);
			if(y==0) {
				return y;
			}
			return y;
		}
		return x;
	}
	
}
