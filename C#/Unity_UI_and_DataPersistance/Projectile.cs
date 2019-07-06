using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Projectile : MonoBehaviour {

    public float power = 1;
    public float lifetime = 1;

    private Rigidbody2D rb2d;
    private int timeAlive = 0;

    private void Start()
    {
        rb2d = GetComponent<Rigidbody2D>();
    }

    private void FixedUpdate()
    {
        //Increment timeAlive and destroy object if timeAlive exceeds lifetime
        timeAlive += 1;
        if (timeAlive > lifetime * 50) Destroy(gameObject);
        
        //Add force going in whatever direction the projectile is currently pointed in
        Vector2 direction = new Vector2(Mathf.Cos((transform.rotation.eulerAngles.z + 90) * Mathf.Deg2Rad), Mathf.Sin((transform.rotation.eulerAngles.z + 90) * Mathf.Deg2Rad));
        rb2d.AddForce(direction * power);
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        Destroy(gameObject);
    }
}
