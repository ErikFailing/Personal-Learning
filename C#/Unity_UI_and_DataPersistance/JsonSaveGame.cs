using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class JsonSaveGame : MonoBehaviour {

    //Creates a new empty save file
    public static void CreateNewSaveGameFile(string name)
    {
        //Takes the name and creates a filename
        string fileName = "SaveGame_" + name + ".txt";

        //Creates the path to the save file
        string path = Path.Combine(Application.persistentDataPath, fileName);

        //If file already exists, reformat name until file doesn't exists
        int count = 1;
        while (File.Exists(path))
        {
            fileName = "SaveGame_" + name + count + ".txt";
            GameManager.currentSaveName = name + count;
            path = Path.Combine(Application.persistentDataPath, fileName);
            count += 1;
            Debug.Log("File already exists, creating new save name: " + fileName);
        }

        //Creates empty output file
        File.CreateText(path);

        //Reports save to console
        Debug.Log(fileName + " created in " + path);
    }

    //Saves the game
    public static void SaveGame(string name, WorldData data)
    {
        //Takes the name and creates a filename
        string fileName = "SaveGame_" + name + ".txt";

        //Creates the path to the save file
        string path = Path.Combine(Application.persistentDataPath, fileName);

        //Reformats the data into a json string
        string jsonString = JsonUtility.ToJson(data);

        //Writes to output file
        using (StreamWriter streamWriter = File.CreateText(path))
        {
            streamWriter.Write(jsonString);
        }

        //Reports save to console
        Debug.Log(fileName + " saved to " + path);
    }

    //Loads the game
    public static WorldData LoadGame(string name)
    {
        //Takes the name and creates a filename
        string filename = "SaveGame_" + name + ".txt";

        //Creates the path to the save file
        string path = Path.Combine(Application.persistentDataPath, filename);

        //Reads data from file and returns it
        using (StreamReader streamReader = File.OpenText(path))
        {
            string jsonString = streamReader.ReadToEnd();

            //Reports save to console
            Debug.Log(filename + " saved to " + path);

            return JsonUtility.FromJson<WorldData>(jsonString);
        }
    }
}
