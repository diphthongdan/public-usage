package view;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ListCell;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.util.Callback;
import songObject.song;
import songObject.songComparator;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Optional;
import java.util.Scanner;

public class ListController {

	@FXML         
	ListView<song> listView;                
	@FXML
	Button add;
	@FXML
	Button delete;
	@FXML
	Button edit;
	@FXML
	TextField addTitle;
	@FXML
	TextField addArtist;
	@FXML
	TextField addAlbum;
	@FXML
	TextField addYear;
	@FXML
	TextField curTitle;
	@FXML
	TextField curArtist;
	@FXML
	TextField curAlbum;
	@FXML
	TextField curYear;
	
	//private ObservableList<String> obsList;              
	private ObservableList<song> obsList;
	public void start(Stage mainStage) {                
		// create an ObservableList 
		// from an ArrayList  
		obsList=FXCollections.observableArrayList(readFile("src/songs.txt"));
		listView.setItems(obsList);
		listView.setCellFactory(new Callback<ListView<song>,ListCell<song>>(){
			@Override
			public ListCell<song> call(ListView<song> l) {
				ListCell<song> cell=new ListCell<song>(){
                    @Override
                    protected void updateItem(song s,boolean bln) {
                        super.updateItem(s, bln);
                        if (s!=null) {
                            setText(s.getTitle()+" by "+s.getArtist());
                        }
                        else if (s==null){
                        	setText(null);
                        }
                    }
                };  
                return cell;
			}
		});
		listView.setItems(obsList); 

		// select the first item
		if(obsList.isEmpty()==false) {
			listView.getSelectionModel().select(0);
		}
		showSong();
		// set listener for the items
		listView
		.getSelectionModel()
		.selectedIndexProperty()
		.addListener(
				(obs, oldVal, newVal) -> 
				showSong());
		//Writes down observableList of songs into local file
		mainStage.setOnCloseRequest(event->{
			writeFile(obsList);
		});

	}
	/*Deletes song selected by user at selected index
	 *After deletion select next song from aforementioned index
	 *If no next song, select previous song
	 *If no songs left, clear current song details
	 */
	@FXML
	private void deleteSong(ActionEvent event) {
				int index=listView.getSelectionModel().getSelectedIndex();
				Alert confirmation = new Alert(AlertType.CONFIRMATION);
				confirmation.setTitle("Confirm delete");
				confirmation.setHeaderText("Delete song confirmation");
				confirmation.setContentText("Do you want to delete song:\n"
						+ obsList.get(index).getTitle()+" by "+obsList.get(index).getArtist()+"?");
				Optional<ButtonType> result = confirmation.showAndWait();
				if (result.get() != ButtonType.OK){
					return;
				}
				obsList.remove(index);
				if(obsList.size()==0) {
					curTitle.clear();
					curArtist.clear();
					curAlbum.clear();
					curYear.clear();
					listView.getSelectionModel().select(-1);
				}else if(obsList.size()==1) {
					listView.getSelectionModel().select(0);
					showSong();
				} else if(obsList.size()<=index) {
					listView.getSelectionModel().select(index-1);
					showSong();
				}else {
					listView.getSelectionModel().select(index);
					showSong();
				}
			}
	/* Edits song selected by user after user has changed fields in current song area
	 * If there are no changes made, error pop up saying saying no changes found
	 * If there is no artist or title or proper year(numeric), error pop up asking user to input both artist and title or proper year(numeric)
	 * If edits are valid but artist and title already exists separately in library, 
	 * 	edits will NOT be performed with error pop up saying song already exists in library
	 * Upon successful edit, selected pre-edit song will be removed and new post-edit song will be added
	 * List will reorganize itself
	 */
	@FXML
	private void editSong(ActionEvent event) {
				int index=listView.getSelectionModel().getSelectedIndex();
				song copy=obsList.get(index);
				String title=curTitle.getText();
				String artist=curArtist.getText();
				String album=curAlbum.getText();
				String year=curYear.getText();
				song toChange=new song(title,artist,album,year);
				if(copy.getTitle().equalsIgnoreCase(title)&&
					copy.getArtist().equalsIgnoreCase(artist)&&
					copy.getAlbum().equalsIgnoreCase(album)&&
					copy.getYear().equalsIgnoreCase(year)) {
					Alert alert=new Alert(AlertType.INFORMATION);
					   alert.setTitle("Error");
					   alert.setHeaderText("Error editing song!");
					   alert.setContentText("No changes to be made found!");
					   alert.showAndWait();
					   return;
				}
				Alert confirmation = new Alert(AlertType.CONFIRMATION);
				confirmation.setTitle("Confirm Edit");
				confirmation.setHeaderText("Edit song confirmation");
				confirmation.setContentText("Do you want to edit song:\n"
						+ copy.getTitle()+" by "+copy.getArtist()+"?");
				Optional<ButtonType> result = confirmation.showAndWait();
				if (result.get() != ButtonType.OK){
					return;
				}
				String check=checkAdd(toChange);
				if(check.length()!=0){
					Alert alert=new Alert(AlertType.INFORMATION);
					   alert.setTitle("Error");
					   alert.setHeaderText("Error editing song!");
					   alert.setContentText(check+"!");
					   alert.showAndWait();
					return;
				}
				obsList.remove(index);
				if(checkForCopy(toChange)==false) {
					Alert alert=new Alert(AlertType.INFORMATION);
					   alert.setTitle("Error");
					   alert.setHeaderText("Error editing song!");
					   alert.setContentText("Song and artist combination already exists in library!");
					   obsList.add(copy);
					   FXCollections.sort(obsList, new songComparator());
					   listView.getSelectionModel().select(index);
					   alert.showAndWait();
					return;
				}
				obsList.add(toChange);
				FXCollections.sort(obsList, new songComparator());
				if(obsList.size()==1) {
					listView.getSelectionModel().select(0);
					showSong();
				} else {
					int i=0;
					for(song s: obsList) {
						if(s.compareTo(toChange)==0) {
							listView.getSelectionModel().select(i);
							showSong();
							break;
						}
						i++;
					}
				}
			}
	/*Adds song based on fields in add song area
	 *If there is no artist or title or proper year(numeric), error pop up asking user to input both artist and title or proper year(numeric)
	 *If fields are valid but artist and title already exists separately in library, 
	 * add will NOT be performed with error pop up saying song already exists in library
	 *Upon successful add, new song object will be created, added into observable library, and library will then be sorted
	 */
	@FXML
	private void addSong(ActionEvent event) {
				String title=addTitle.getText();
				String artist=addArtist.getText();
				String album=addAlbum.getText();
				String year=addYear.getText();
				Alert confirmation = new Alert(AlertType.CONFIRMATION);
				confirmation.setTitle("Confirm Add");
				confirmation.setHeaderText("Add song confirmation");
				confirmation.setContentText("Do you you to add song:\n"
						+ title+" by "+artist+"?");
				Optional<ButtonType> result = confirmation.showAndWait();
				if (result.get() != ButtonType.OK){
					return;
				}
				song temp=new song(title,artist,album,year);
				String check=checkAdd(temp);
				if(check.length()!=0){
					Alert alert=new Alert(AlertType.INFORMATION);
					   alert.setTitle("Error");
					   alert.setHeaderText("Error adding song!");
					   alert.setContentText(check+"!");
					   alert.showAndWait();
					return;
				}
				if(checkForCopy(temp)==false) {
					Alert alert=new Alert(AlertType.INFORMATION);
					   alert.setTitle("Error");
					   alert.setHeaderText("Error adding song!");
					   alert.setContentText("Song and artist combination already exists in library!");
					   alert.showAndWait();
					return;
				}
				obsList.add(temp);
				FXCollections.sort(obsList, new songComparator());
				addTitle.clear();
				addArtist.clear();
				addAlbum.clear();
				addYear.clear();
				if(obsList.size()==1) {
					listView.getSelectionModel().select(0);
				} else {
					int i=0;
					for(song s: obsList) {
						if(s.compareTo(temp)==0) {
							listView.getSelectionModel().select(i);
							break;
						}
						i++;
					}
				}
			}
	//Shows selected song is obsList
	private void showSong() {
		if(listView.getSelectionModel().getSelectedIndex()<0) {
			return;
		}
		song s=listView.getSelectionModel().getSelectedItem();
		curTitle.setText(s.getTitle());
		curArtist.setText(s.getArtist());
		curAlbum.setText(s.getAlbum());
		curYear.setText(s.getYear());
	}
	//Checks if fields are valid
	private String checkAdd(song s) {
		if(s.getTitle().length()==0||s.getArtist().length()==0) {
			return "Please fill out both artist and title before adding";
		}
		if(s.getYear()==""||s.getYear().length()==0) {
			return "";
		} else {
			for(char c:s.getYear().toCharArray()) {
				if(Character.isDigit(c)==false) {
					return "Please use only numbers when entering year";
				}
			}
		}
		return "";
	}
	//Checks to see if song already exists in obsList
	private boolean checkForCopy(song s) {
		for(int i=0;i<obsList.size();i++) {
			if(s.compareTo(obsList.get(i))==0) {
				return false;
			}
		}
		return true;
	}
	/* Takes in String denoting file path for song
	* Format of text file should be
	*<title>:<artist>:<album>:<year><newLineChar>
	*NOTE: MUST HAVE NEW LINE CHARACTER AT END OR ELSE READ WILL NOT WORK
	*Returns sorted ArrayList of type song
	*/
	private ArrayList<song> readFile(String file) {
		ArrayList<song> songList=new ArrayList<song>();
		Path f=Paths.get(file);
		Scanner s=null;
		try {
			if(new File(file).exists()==false) {
				return songList;
			}
			s = new Scanner(f);
			s.useDelimiter(":|\\n"); //Use : and new line character as delimiter
			while(s.hasNext()) {
				String title=s.next();
				String artist=s.next();
				String album=s.next();
				String year=s.next();
				song temp=new song(title,artist,album,year);
				songList.add(temp);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
		s.close();
		Collections.sort(songList);
		return songList;
	}
	/* Takes in ObservableList of type song
	 * Will OVERWRITE any file with same name with new song list, this case "src/songs.txt"
	 * Will write in format <title>:<artist>:<album>:<year><newLineChar> to new text file
	 * Returns nothing
	 */
	private void writeFile(ObservableList<song> songs) {
		PrintWriter writer;
	  	try {
	  			File file = new File ("src/songs.txt");
	  			file.createNewFile();
	  			writer = new PrintWriter(file);
				for(song s: songs)
		    	  {
		    		  writer.print(s.getTitle()+":");
		    		  writer.print(s.getArtist()+":");
		    		  writer.print(s.getAlbum()+":");
		    		  writer.print(s.getYear()+"\n");
		    		  
		    	  }
		    	 writer.close(); 
	} catch (Exception e) {
		e.printStackTrace();
		}  
	}
}
