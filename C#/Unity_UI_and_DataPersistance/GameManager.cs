using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;
using System;
using UnityEngine.Tilemaps;

public class GameManager : MonoBehaviour {
    
    public static string currentSaveName;
    public List<GameObject> prefabList;//A list of prefabs to instantiate from when loading the game.
    public WorldData worldData;
    public static GameObject player;

    private void Start()
    {
        SetUp();
    }

    private void Update()
    {
        if (Input.GetKeyDown("escape")) EscapeMenu();
    }
    
    public void ReturnToTitleScreen()//Returns to titlescreen
    {
        SceneManager.LoadSceneAsync("TitleScreen");
        Debug.Log("Returning to title screen.");

        //SaveGame
        SaveWorld();
        Time.timeScale = 1;
    }
    public void EscapeMenu()//Determines if the escape menu should be closed or opened
    {
        GameObject go = GameObject.Find("Canvas");
        if (go.transform.Find("EscapeMenu").gameObject.activeSelf) CloseEscapeMenu();
        else OpenEscapeMenu();
    }
    public void OpenEscapeMenu()//Opens the escape menu
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("EscapeMenu").gameObject.SetActive(true);
        Time.timeScale = 0;
    }
    public void CloseEscapeMenu()//Closes the escape menu
    {
        GameObject go = GameObject.Find("Canvas");
        go.transform.Find("EscapeMenu").gameObject.SetActive(false);
        Time.timeScale = 1;
    }

    public void SetUp()//Sets up the game to be played
    {
        //Pause the game while setting up
        Time.timeScale = 0;

        worldData = new WorldData();
        if (ShouldLoad())
        {
            LoadWorld();
            GameObject.Find("Main Camera").GetComponent<CameraController>().target = player; //Reassign camera
        }
        if (player == null) { player = GameObject.Find("Player"); }
        

        //Unpause the game after finishing setup
        Time.timeScale = 1;
    }

    public bool SaveWorld()//Saves the the current world to the save file
    {
        SaveSettings();
        SaveUnits();
        //SaveTerrain();
        //Write to file
        JsonSaveGame.SaveGame(currentSaveName, worldData);
        return true;
    }
    public void SaveSettings()//Saves all the settings in the world to WorldData
    {
        worldData.settingsData.cameraSize = GameObject.Find("Main Camera").GetComponent<Camera>().orthographicSize;
    }
    public void SaveUnits()//Saves all the units in the world to WorldData 
    {
        worldData.unitData.Clear(); //Deletes all units from the worldData unitData list
        //Foreach active unit in the scene
        foreach (GameObject go in GameObject.FindGameObjectsWithTag("Unit"))
        {
            UnitData unitData = new UnitData(go.GetComponent<AssignedPrefab>().prefab, 
                go.transform, go.GetComponent<Rigidbody2D>(), go.GetComponent<Tags>(), go.GetComponent<Health>()); //Create UnitData for the unit
            worldData.unitData.Add(unitData); //Add UnitData to the worldData list
        }
    }

    public bool ShouldLoad()//Determines if the game should load the world or not
    {
        if (SceneManager.GetActiveScene().name == "EmptyGameWorld") return true;
        return false;
    }
    public bool LoadWorld()//Loads the data from the save file into the current world 
    {
        //Read in from file
        worldData = JsonSaveGame.LoadGame(currentSaveName);
        LoadSettings();
        LoadUnits();
        //LoadTerrain();
        return true;
    }
    public void LoadSettings()//Loads all the settings from WorldData to the world
    {
        GameObject.Find("Main Camera").GetComponent<Camera>().orthographicSize = worldData.settingsData.cameraSize;
    }
    public void LoadUnits()//Loads all the units from WorldData into the world
    {
        //Foreach UnitData in the current WorldData unitData list
        foreach (UnitData unitData in worldData.unitData)
        {
            //Find the prefab and instantiate it in the right position and rotation
            GameObject newUnit = Instantiate(prefabList[FindInPrefabList(unitData.prefabName)], 
                unitData.position, unitData.rotation);
            newUnit.transform.localScale = unitData.scale; //Set the newly instantiated unit's scale

            newUnit.GetComponent<Rigidbody2D>().velocity = unitData.velocity;
            newUnit.GetComponent<Rigidbody2D>().inertia = unitData.inertia;

            newUnit.GetComponent<Tags>().nickname = unitData.nickname;
            newUnit.GetComponent<Tags>().species = unitData.species;
            newUnit.GetComponent<Tags>().faction = unitData.faction;
            newUnit.GetComponent<Tags>().ranking = unitData.ranking;
            newUnit.GetComponent<Tags>().unitSize = unitData.unitSize;

            newUnit.GetComponent<Tags>().level = unitData.level;
            newUnit.GetComponent<Tags>().experience = unitData.experience;
            newUnit.GetComponent<Tags>().experienceWorth = unitData.experienceWorth;

            newUnit.GetComponent<Health>().maxHealth = unitData.maxHealth;
            newUnit.GetComponent<Health>().currentHealth = unitData.currentHealth;

            if (unitData.prefabName == "Player") player = newUnit;
        }
    }
    private int FindInPrefabList(string nameToSearchFor)//Find the prefab in the prefablist with a matching name
    {
        int i = 0;
        bool found = false;
        while (!found && i < prefabList.Count)
        {
            if (nameToSearchFor == prefabList[i].name) found = true; //If name was found in prefablist
            else i += 1;
        }
        if (found == false) Debug.Log("Not found in prefabList: " + nameToSearchFor);
        return i;
    }

    public static void DestroyGroundsTile(Vector3 pos)//Destroy's a tile in the grounds
    {
        GameObject go = GameObject.Find("Grid");
        Vector3Int miningpos = go.GetComponent<Grid>().WorldToCell(pos);
        go.transform.Find("TheGrounds").GetComponent<Tilemap>().SetTile(miningpos, null);
    }
    public static void Recur()//Recurs the world
    {
        GameManager.ReturnPlayerToSafeZone();
        InputManager.SetRecurToFalse();
    }
    public static void ReturnPlayerToSafeZone()//Returns the player to a safe zone
    {
        player.transform.position = new Vector3(0, 0, 0);
    }
}

[Serializable]
public class WorldData
{
    public WorldData()
    {
        unitData = new List<UnitData>();
        settingsData = new SettingsData();
    }

    public SettingsData settingsData;
    public List<UnitData> unitData;
}

[Serializable]
public class SettingsData
{
    public float cameraSize;
}

[Serializable]
public class UnitData
{
    public UnitData(string n, Transform t, Rigidbody2D rb2d, Tags tags, Health health)
    {
        prefabName = n;

        position = t.position;
        rotation = t.rotation;
        scale = t.localScale;

        velocity = rb2d.velocity;
        inertia = rb2d.inertia;

        nickname = tags.nickname;
        species = tags.species;
        faction = tags.faction;
        ranking = tags.ranking;
        unitSize = tags.unitSize;

        level = tags.level;
        experience = tags.experience;
        experienceWorth = tags.experienceWorth;

        maxHealth = health.maxHealth;
        currentHealth = health.currentHealth;
    }

    public string prefabName;

    public Vector3 position;
    public Quaternion rotation;
    public Vector3 scale;

    public Vector3 velocity;
    public float inertia;

    public string nickname;
    public string species;
    public string faction;
    public int ranking;
    public float unitSize;

    public int level;
    public int experience;
    public int experienceWorth;
    public int maxHealth;
    public int currentHealth;
}
