using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//This class moves the gameobject it is attached to back and forth between its initial position
//and the specified end positon
public class MoveLoop : MonoBehaviour {

    public float time = 1;
    public float maxSpeed = 100;
    public Vector2[] movePositions;
    
    private Vector2 velocity;
    private int movingToPosition = 0;
    

    private void FixedUpdate()
    {
        //If 0 movePositions, stay still.
        if (movePositions.Length == 0) return;

        //If position has been reached
        if ( (Vector2) transform.position == movePositions[movingToPosition])
        {
            //Decide what position we go to next
            //If last position, return to start
            if (movingToPosition + 1 == movePositions.Length)
            {
                movingToPosition = 0;
            }
            else movingToPosition += 1;
        }

        //Move to new position
        Vector2 newPosition;
        newPosition = Vector2.SmoothDamp(transform.position, movePositions[movingToPosition], ref velocity, time, maxSpeed, Time.deltaTime);
        GetComponent<Rigidbody2D>().MovePosition(newPosition);
    }
}
