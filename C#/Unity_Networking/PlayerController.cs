using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

// This object is technically recognized by unity as the "player" to be spawned upon server start.
// However this is really just where we control the player connection and setup.
// The actual player object is PlayerUnit

public class PlayerController : NetworkBehaviour
{

    public GameObject PlayerPrefab;

    public List<GameObject> controlledObjects;

    // Use this for initialization
    void Start()
    {
        if (!isLocalPlayer) return;
        CmdSpawnPlayerUnit();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    //////////////////////       COMMANDS       ////////////////////////////
    // send information from Client --> Server. 
    // It can only be used if the client owns the object and has authority.

    [Command]
    void CmdSpawnPlayerUnit()
    {
        // Instantiate Player on the server
        GameObject go = Instantiate(PlayerPrefab);
        // Now that the object exists on the server, propagate it to all
        // The clients (and also wire up the NetworkIdentity)
        NetworkServer.SpawnWithClientAuthority(go, connectionToClient);
        TargetAddPlayerToControlled(connectionToClient, go);
    }

    //////////////////////         [TargetRPC]       /////////////////////////
    // sends information from Server --> a client, only sends to 1 specific client(not all clients)

    [TargetRpc]
    void TargetAddPlayerToControlled(NetworkConnection target, GameObject playerUnit)
    {
        gameObject.name = "Local Player Controller";
        controlledObjects.Add(playerUnit);
        playerUnit.name = "Local Player";
        GameObject.Find("Camera").GetComponent<Camera>().GetComponent<CameraController>().setFocus(playerUnit);

    }

}
