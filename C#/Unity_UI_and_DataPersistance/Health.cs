using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Health : MonoBehaviour
{
    public int currentHealth = 1;
    public int maxHealth = 1;

    /// <summary>
    /// Deals damage to the unit. If damage exceeds unit's current health, calls death()
    /// </summary>
    /// <param name="damage"></param>
	public void TakeDamage(int damage)
    {
        if (currentHealth - damage > 0)
        {
            currentHealth -= damage;
        }
        else
        {
            TrueDeath();
        }
    }

    /// <summary>
    /// Heals the unit by the amount. If it exceeds max hp, unit just heals to full
    /// </summary>
    /// <param name="heal"></param>
    public void Heal(int heal)
    {
        if (currentHealth + heal > maxHealth)
        {
            currentHealth = maxHealth;
        }
        else currentHealth += heal;
    }

    /// <summary>
    /// Kills the unit, destroying it from the game forever.
    /// </summary>
    private void TrueDeath()
    {
        Destroy(gameObject);
    }

}
