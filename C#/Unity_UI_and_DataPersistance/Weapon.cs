using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Weapon : MonoBehaviour
{
    private void OnCollisionStay2D(Collision2D other)
    {
        DealDamage(other.gameObject);
    }

    private void DealDamage(GameObject victim)
    {
        victim.GetComponent<Health>().TakeDamage(1);
    }

}
