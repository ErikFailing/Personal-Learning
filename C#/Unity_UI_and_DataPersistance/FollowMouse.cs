using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowMouse : MonoBehaviour {

    Vector2 MousePosition;
    Vector2 CurrentVelocity;

    // Update is called once per frame
    void Update()
    {
        //Get inputs
        MousePosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
    }

    private void FixedUpdate()
    {
        //Move player
        transform.position = (Vector3)Vector2.SmoothDamp(transform.position, MousePosition, ref CurrentVelocity, 0.08f) + new Vector3(0, 0, 9);
    }
}
