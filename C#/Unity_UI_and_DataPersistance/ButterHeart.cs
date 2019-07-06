using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ButterHeart : MonoBehaviour {

    Vector2 MousePosition;
    Vector2 CurrentVelocity;
    Vector2 TurnVelocity;

    // Update is called once per frame
    void Update()
    {
        //Get inputs
        MousePosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
    }

    private void FixedUpdate()
    {
        //Move ButterHeart
        Vector2 direction = new Vector2(MousePosition.x - transform.position.x, MousePosition.y - transform.position.y);
        transform.up = Vector2.SmoothDamp(transform.up, direction, ref TurnVelocity, 0.10f, 18, Time.deltaTime);
        float distance = Mathf.Abs(transform.position.x - MousePosition.x) + Mathf.Abs(transform.position.y - MousePosition.y);
        if (distance > .2)
            transform.position = (Vector3)Vector2.SmoothDamp(transform.position, MousePosition, ref CurrentVelocity, 0.15f) + new Vector3(0, 0, 9);
    }
}
