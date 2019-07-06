using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//This class rotates its gameobject each fixed update
public class Spin : MonoBehaviour {

    public float speed = 1;

    private void FixedUpdate()
    {
        GetComponent<Rigidbody2D>().MoveRotation(GetComponent<Rigidbody2D>().rotation - speed);
    }

}
