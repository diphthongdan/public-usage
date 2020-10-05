package app;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import view.ListController;

public class SongLib extends Application {
	@Override
	public void start(Stage primaryStage) throws Exception {
		FXMLLoader loader = new FXMLLoader();   
		loader.setLocation(getClass().getResource("/view/list.fxml"));
		AnchorPane root = (AnchorPane)loader.load();
		ListController listController = loader.getController();
		listController.start(primaryStage);
		Scene scene = new Scene(root, 850, 450);
		primaryStage.setScene(scene);
		primaryStage.setResizable(false);
		primaryStage.setTitle("Song Library");
		primaryStage.show(); 
	}
	public static void main(String[] args) {
		launch(args);
	}
}
