using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class PlayerUnit : NetworkBehaviour {

    public Rigidbody2D player;
    public Vector2 playerTurnVelocity;
    private int horizontalMovement;
    private int verticalMovement;
    public GameObject camG;
    private Camera cam;
    private Vector3 mousePosition;

    [SyncVar]
    public float xDifference;
    [SyncVar]
    public float yDifference;


    // Use this for initialization
    void Start () {
        player = GetComponent<Rigidbody2D>();
        if (!localPlayerAuthority) return;
        camG = GameObject.Find("Camera");
        cam = camG.GetComponent<Camera>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!hasAuthority) return;
        GetPlayerInputs();
    }

    //Gets the inputs the player makes
    private void GetPlayerInputs()
    {
        if (Input.GetAxis("Horizontal") > 0) horizontalMovement = 1;
        else if (Input.GetAxis("Horizontal") < 0) horizontalMovement = -1;
        else horizontalMovement = 0;

        if (Input.GetAxis("Vertical") > 0) verticalMovement = 1;
        else if (Input.GetAxis("Vertical") < 0) verticalMovement = -1;
        else verticalMovement = 0;

        mousePosition = Input.mousePosition;
        mousePosition = cam.ScreenToWorldPoint(mousePosition);

    }

    //Fixed update is called 50 times per second, independent of frame rate.
    private void FixedUpdate()
    {
        if (!hasAuthority)
        {
            SyncRotation();
            return;
        }
        DoPlayerInputs();
    }

     void SyncRotation()
    {
        Vector2 direction =  new Vector2(xDifference, yDifference);
        player.transform.up = Vector2.SmoothDamp(player.transform.up, direction, ref playerTurnVelocity, 0.15f, 18, Time.deltaTime);
    }

    //Takes the inputs from the player and actually does things with them!
    private void DoPlayerInputs()
    {
        float movespeed = 2000.0f;

        //Faces the player in the direction the mouse is pointing.
        //Freeze rotation prevents angular velocity syncing over the network, so we need to...
        // A. Sync rotation manually
        // B. rotate via addtorque and unfreeze rotation

        CmdSyncRotation(mousePosition.x - transform.position.x, mousePosition.y - transform.position.y);
        Vector2 direction = new Vector2(mousePosition.x - transform.position.x, mousePosition.y - transform.position.y);

        player.transform.up = Vector2.SmoothDamp(player.transform.up, direction, ref playerTurnVelocity, 0.15f, 18, Time.deltaTime);

        /*float hypotunuseLength = (Mathf.Sqrt(Mathf.Pow((mousePosition.x - transform.position.x), 2) + Mathf.Pow((mousePosition.y - transform.position.y), 2)));
        float directionInRadians = Mathf.Atan((mousePosition.y - transform.position.y) / (mousePosition.x - transform.position.x));
        float directionInDegrees = (180 / Mathf.PI) * directionInRadians;
        Quaternion directionQ = Quaternion.Euler(0, 0, directionInDegrees);
        player.transform.rotation = directionQ; */


        // 8 direction movement

        if (horizontalMovement == 1 && verticalMovement == 0)
        {
            //player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(movespeed, 0)); // Right
        }
        else if (horizontalMovement == 1 && verticalMovement == -1)
        {
            //player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(movespeed / 2, -movespeed / 2)); // Down - Right
        }
        else if (horizontalMovement == 0 && verticalMovement == -1)
        {
            //player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(0, -movespeed)); // Down
        }
        else if (horizontalMovement == -1 && verticalMovement == -1)
        {
            // player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(-movespeed / 2, -movespeed / 2)); // Down - Left
        }
        else if (horizontalMovement == -1 && verticalMovement == 0)
        {
            //player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(-movespeed, 0)); // Left
        }
        else if (horizontalMovement == -1 && verticalMovement == 1)
        {
            //player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(-movespeed / 2, movespeed / 2)); // Up - Left
        }
        else if (horizontalMovement == 0 && verticalMovement == 1)
        {
            //player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(0, movespeed)); // Up
        }
        else if (horizontalMovement == 1 && verticalMovement == 1)
        {
            //player.velocity = (new Vector2(player.velocity.x * 0.2f, player.velocity.y * 0.2f));
            player.AddForce(new Vector2(movespeed / 2, movespeed / 2)); // Up - Right
        }
        else if (horizontalMovement == 0 && verticalMovement == 0)
        {
            //player.velocity = (new Vector2(0, 0)); // Stationary
        }


    }
    
    [Command]
    void CmdSyncRotation(float xDiff, float yDiff)
    {
        xDifference = xDiff;
        yDifference = yDiff;
    }
}

