using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class Player : MonoBehaviour
{
    private Rigidbody2D rb2d;
    private Vector2 TurnVelocity;

    // Start is called before the first frame update
    void Start()
    {
        rb2d = GetComponent<Rigidbody2D>();
    }

    void Update()
    {
        if (Input.GetMouseButtonDown(1))
        {
            PrimaryAction();
        }
        
    }

    private void FixedUpdate()
    {
        
        Vector2 direction = new Vector2(InputManager.MousePositionInWorld.x - transform.position.x, InputManager.MousePositionInWorld.y - transform.position.y);
        transform.up = Vector2.SmoothDamp(transform.up, direction, ref TurnVelocity, 0.10f, 18, Time.deltaTime);

        float movespeed = 100.0f;
        if (InputManager.movementDirection == new Vector2(1, 0)) rb2d.AddForce(new Vector2(movespeed, 0)); // Right
        else if (InputManager.movementDirection == new Vector2(1, -1)) rb2d.AddForce(new Vector2(movespeed / 2, -movespeed / 2)); // Down - Right
        else if (InputManager.movementDirection == new Vector2(0, -1)) rb2d.AddForce(new Vector2(0, -movespeed)); // Down
        else if (InputManager.movementDirection == new Vector2(-1, -1)) rb2d.AddForce(new Vector2(-movespeed / 2, -movespeed / 2)); // Down - Left
        else if (InputManager.movementDirection == new Vector2(-1, 0)) rb2d.AddForce(new Vector2(-movespeed, 0)); // Left
        else if (InputManager.movementDirection == new Vector2(-1, 1)) rb2d.AddForce(new Vector2(-movespeed / 2, movespeed / 2)); // Up - Left
        else if (InputManager.movementDirection == new Vector2(0, 1)) rb2d.AddForce(new Vector2(0, movespeed)); // Up
        else if (InputManager.movementDirection == new Vector2(1, 1)) rb2d.AddForce(new Vector2(movespeed / 2, movespeed / 2)); // Up - Right

        if (InputManager.recur == true) GameManager.Recur();
    }

    private void PrimaryAction()//Player takes their current primary action
    {

    }

}
