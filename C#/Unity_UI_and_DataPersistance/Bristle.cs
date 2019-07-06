using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Deals damage to anything it touches excluding other pieces of the same unit and then self destructs.
/// </summary>
public class Bristle : MonoBehaviour
{
    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.gameObject.transform.IsChildOf(transform.parent)) return;
        DealDamage(other.gameObject);
    }

    private void DealDamage(GameObject victim)
    {
        victim.transform.parent.gameObject.GetComponent<Health>().TakeDamage(1);
        SelfDestruct();
    }

    private void SelfDestruct()
    {
        Destroy(gameObject);
    }
}
