using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour {
    
    public int maximumLivingSpawns = 3;
    public GameObject unitToSpawn;
    public float spawnDelay = 10;
    public int unitsPerSpawn = 1;


    private int currentLivingSpawns = 0;
    private float unitSize;
    public int spawnTimer = 0;
    private int layerMaskSpawnPoint;   // 0000 0000 0000 0000     0001 1000 0000 0000  OR  6144
    private Transform spawnsParent;
    private Transform spawnZone;
    private float spawnRange;

    private void Start()
    {
        //Get the size of the unit this spawner is spawning 
        unitSize = unitToSpawn.GetComponent<Tags>().unitSize;

        //Set layermask
        layerMaskSpawnPoint = 6144;

        //Get the child transform to store projectiles fired under
        spawnsParent = transform.Find("Spawns");

        //Get the spawnzone
        spawnZone = transform.Find("SpawnZone");
        spawnRange = spawnZone.localScale.x * 2.5f;
    }

    private void FixedUpdate()
    {
        //If spawnTimer is less than cap, tick up
        if (spawnTimer < 50000) spawnTimer += 1;

        //Get current living spawns
        currentLivingSpawns = spawnsParent.childCount;

        //If spawnTimer is less than spawndelay times 50, return
        if (spawnTimer < spawnDelay * 50) return;

        //If current number of living spawns equals or exceeds maximum spawns, return
        if (currentLivingSpawns >= maximumLivingSpawns) return;

        //Attempt to spawn units
        for (int i = 0; i <= unitsPerSpawn; i += 1)
        {
            //If current number of living spawns equals or exceeds maximum spawns, break
            if (currentLivingSpawns >= maximumLivingSpawns) break;

            //Generate a random spawn point within the given range to try
            Vector2 spawnPoint = new Vector2(transform.position.x + Random.Range(-(spawnRange / 2), (spawnRange / 2)), transform.position.y + Random.Range(-(spawnRange / 2), (spawnRange / 2)));

            //If spawnpoint has nothing in it, spawn unit
            if (Physics2D.OverlapCircle(spawnPoint, unitSize, layerMaskSpawnPoint) == null) //definately going to need to layermask this
            {
                Instantiate(unitToSpawn, spawnPoint, Quaternion.Euler(0, 0, 0), spawnsParent);
                currentLivingSpawns += 1;
            }

        }

        //Reset spawnTimer
        spawnTimer = 0;

    }

}
