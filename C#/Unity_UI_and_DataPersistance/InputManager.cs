using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InputManager : MonoBehaviour
{
    static public Vector2 MousePositionInWorld;
    static public Vector2 movementDirection;
    static public bool cancel;
    static public bool accept;
    static public bool recur;

    // Update is called once per frame
    void Update()
    {
        MousePositionInWorld = Camera.main.ScreenToWorldPoint(Input.mousePosition);

        int horizontalMovement;
        int verticalMovement;
        if (Input.GetAxis("Horizontal") > 0) horizontalMovement = 1;
        else if (Input.GetAxis("Horizontal") < 0) horizontalMovement = -1;
        else horizontalMovement = 0;
        if (Input.GetAxis("Vertical") > 0) verticalMovement = 1;
        else if (Input.GetAxis("Vertical") < 0) verticalMovement = -1;
        else verticalMovement = 0;
        movementDirection = new Vector2(horizontalMovement, verticalMovement);

        if (Input.GetAxis("Cancel") > 0) cancel = true;
        else cancel = false;

        if (Input.GetAxis("Accept") > 0) accept = true;
        else accept = false;

        if (Input.GetAxis("Recur") > 0) recur = true;
    }

    public static void SetRecurToFalse()
    {
        recur = false;
    }

}
