using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AmbleAnt : MonoBehaviour {

    private float moveRange = 2.5f;
    private Vector2 TurnVelocity;

    private void Start()
    {
        
    }

    private void FixedUpdate()
    {
        //Get a random point to move towards based on the direction the ambleant is currently facing
        Vector2 movePoint = new Vector2(transform.position.x + Random.Range(-(moveRange / 2), (moveRange / 2)), transform.position.y + Random.Range(-(moveRange / 2), (moveRange / 2)));


        //Move towards the point we just casted to
        //Get direction direction in a raw form
        Vector2 direction = movePoint - (Vector2)transform.position;
        transform.up = Vector2.SmoothDamp(transform.up, direction, ref TurnVelocity, 0.10f, 18, Time.deltaTime);
        //Convert direction into a usable fraction (%x, %y)
        float total = Mathf.Abs(direction.x) + Mathf.Abs(direction.y);
        //return if total is 0
        if (total == 0) return;
        direction = new Vector2(direction.x / total, direction.y / total);

        //Apply force
        GetComponent<Rigidbody2D>().AddForce(direction * 10);

    }

}
