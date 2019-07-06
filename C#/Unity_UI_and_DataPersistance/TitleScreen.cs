using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using TMPro;
using System.IO;

public class TitleScreen : MonoBehaviour {

    //The prefab used for instantiating Load Game Buttons
    public GameObject loadGameButton;

    //The load game button currently selected
    private string selectedSaveGameFile = "";


    //Starts a new game
    public void StartNewGame()
    {
        //Sets GameManager's saveName to the name entered by the user
        GameObject go = GameObject.Find("Canvas");
        go = go.transform.Find("NewGameMenu").gameObject;
        GameManager.currentSaveName = go.transform.Find("NameInput").GetComponent<TMP_InputField>().text;
        //Creates a new save game file
        JsonSaveGame.CreateNewSaveGameFile(GameManager.currentSaveName);

        SceneManager.LoadSceneAsync("NewGameWorld");
        Debug.Log("Starting a new game.");

    }

    //Opens the new game menu
    public void OpenNewGameMenu()
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("MainMenu").gameObject.SetActive(false);
        go.transform.Find("NewGameMenu").gameObject.SetActive(true);

        //Selects Textbox
        go.transform.Find("NewGameMenu").Find("NameInput").GetComponent<TMP_InputField>().Select();
    }

    //Enables the start new game button if the name isn't empty
    public void ToggleStartNewGameButton()
    {
        GameObject go = GameObject.Find("Canvas");
        go = go.transform.Find("NewGameMenu").gameObject;
        GameObject button = go.transform.Find("StartNewGame").gameObject;
        string name = go.transform.Find("NameInput").GetComponent<TMP_InputField>().text;

        if (name != null && name != "")
            button.GetComponent<Button>().interactable = true;
        else button.GetComponent<Button>().interactable = false;
    }

    //Close the new game menu
    public void CloseNewGameMenu()
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("NewGameMenu").gameObject.SetActive(false);
        go.transform.Find("MainMenu").gameObject.SetActive(true);
    }

    //Opens the Load Game menu
    public void OpenLoadGameMenu()
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("MainMenu").gameObject.SetActive(false);
        go.transform.Find("LoadGameMenu").gameObject.SetActive(true);

        //Search save file repository and display save files to load
        DirectoryInfo dir = new DirectoryInfo(Application.persistentDataPath);
        FileInfo[] info = dir.GetFiles("*.*");
        List<string> fileNames = new List<string>();
        foreach (FileInfo f in info)
        {
            //If it is a save file add it's name to a list
            if (f.Name.Contains("SaveGame_"))
            {
                string name = f.Name;
                name = name.Replace("SaveGame_", "");
                name = name.Replace(".txt", "");
                fileNames.Add(name);
            }
        }
        //Instantiate Load Game Buttons for each save file
        go = go.transform.Find("LoadGameMenu").Find("LoadFileMenuScroller").Find("Viewport").Find("Content").gameObject;
        foreach (string s in fileNames)
        {
            //Instantiate a button corresponding to the save game name
            GameObject button = Instantiate(loadGameButton, go.transform);
            button.name = "LoadGame_" + s;
            //Name the button appropiately
            button.transform.Find("FileName").GetComponent<TextMeshProUGUI>().text = s;
            //Assign the button an onclick function
            button.GetComponent<Button>().onClick.AddListener(delegate { SwitchSelectedSaveGameFile(s); });
        }
    }

    //Switches which save game file is currently being selected
    public void SwitchSelectedSaveGameFile(string file)
    {
        selectedSaveGameFile = file;

        //Enables and disables load and delete save game buttons based on what is currently selected
        GameObject go = GameObject.Find("Canvas");
        go = go.transform.Find("LoadGameMenu").gameObject;
        GameObject loadButton = go.transform.Find("LoadSaveGame").gameObject;
        GameObject deleteButton = go.transform.Find("DeleteSaveGame").gameObject;
        if (selectedSaveGameFile != null && selectedSaveGameFile != "")
        {
            loadButton.GetComponent<Button>().interactable = true;
            deleteButton.GetComponent<Button>().interactable = true;
        }
        else
        {
            loadButton.GetComponent<Button>().interactable = false;
            deleteButton.GetComponent<Button>().interactable = false;
        }
    }

    //Opens the main menu
    public void CloseLoadGameMenu()
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("LoadGameMenu").gameObject.SetActive(false);
        go.transform.Find("MainMenu").gameObject.SetActive(true);

        //Delete all the options buttons created
        go = go.transform.Find("LoadGameMenu").Find("LoadFileMenuScroller")
            .Find("Viewport").Find("Content").gameObject;
        for (int i = go.transform.childCount - 1; i >= 0; i -= 1)
        {
            Destroy(go.transform.GetChild(i).gameObject);
        }
    }

    //Opens the options menu
    public void OpenOptionsMenu()
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("MainMenu").gameObject.SetActive(false);
        go.transform.Find("OptionsMenu").gameObject.SetActive(true);
    }

    //Opens the main menu
    public void CloseOptionsMenu()
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("OptionsMenu").gameObject.SetActive(false);
        go.transform.Find("MainMenu").gameObject.SetActive(true);
    }

    //Deletes the first instance of the named file
    public void DeleteSaveGameFile()
    {
        string file = "SaveGame_" + selectedSaveGameFile + ".txt";
        DirectoryInfo dir = new DirectoryInfo(Application.persistentDataPath);
        FileInfo[] info = dir.GetFiles("*.*");
        foreach (FileInfo f in info)
        {
            //If it is the save file, delete it and the button representing it
            if (f.Name == file)
            {
                File.Delete(f.FullName);
                Debug.Log("Save file: " + file + " deleted.");
                Destroy(GameObject.Find("Canvas").transform.Find("LoadGameMenu").Find("LoadFileMenuScroller")
                    .Find("Viewport").Find("Content").Find("LoadGame_" + selectedSaveGameFile).gameObject);
                SwitchSelectedSaveGameFile("");
                return;
            }
        }
    }

    //Loads a game save file if it matches the given string
    public void LoadSaveGameFile()
    {
        //Sets GameManager's saveName to the name entered by the user
        GameManager.currentSaveName = selectedSaveGameFile;

        SceneManager.LoadSceneAsync("EmptyGameWorld");
        Debug.Log("Loading game: " + selectedSaveGameFile);
    }

    //Opens the folder containing the games saved
    public void OpenSavedGamesFolder()
    {
        System.Diagnostics.Process.Start(Application.persistentDataPath);
    }

    //Quits the game
    public void QuitGame()
    {
        Application.Quit();
    }
}
