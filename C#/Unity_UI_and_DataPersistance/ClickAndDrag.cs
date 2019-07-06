using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClickAndDrag : MonoBehaviour {

    public float power = 1f;

    private Vector2 offset;
    
    private void OnMouseDown()
    {
        Vector2 mousePosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        offset = mousePosition - (Vector2) transform.position;
    }

    private void OnMouseDrag()
    {
        //Initialize variables
        Vector2 mousePosition;
        Vector2 endPosition;
        Vector2 direction;
        float force;
        float total;

        //Calculate variables
        mousePosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        endPosition = mousePosition - offset;

        //Get direction direction in a raw form
        direction = endPosition - (Vector2) transform.position;
        //Convert direction into a usable fraction (%x, %y)
        total = Mathf.Abs(direction.x) + Mathf.Abs(direction.y);
        //return if total is 0
        if (total == 0) return;
        direction = new Vector2(direction.x / total, direction.y / total);

        //Calculate how much force to apply scaling on distance from current point to end point
        if (Vector2.Distance(endPosition, transform.position) < 5)
            force = power * Vector2.Distance(endPosition, transform.position);
        else  force = power * 5; 

        //Apply force
        GetComponent<Rigidbody2D>().AddForce(direction * force);



        //ALTERNATIVE METHODS TO MOVE THE GAMEOBJECT

        //transform.position = endPosition;

        //GetComponent<Rigidbody2D>().MovePosition(endPosition);

        //<Rigidbody2D>().addForceAtPoint

        //GetComponent<Rigidbody2D>().AddForce(direction * force, ForceMode2D.Impulse);
    }
}
