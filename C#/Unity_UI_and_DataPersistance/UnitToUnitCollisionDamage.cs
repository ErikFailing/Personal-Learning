using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UnitToUnitCollisionDamage : MonoBehaviour
{
    public int damage = 1;

    private void OnTriggerStay2D(Collider2D other)
    {
        DealDamage(other.transform.parent.gameObject);
    }

    private void DealDamage(GameObject victim)
    {
        victim.GetComponent<Health>().TakeDamage(damage);
    }
}
