using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class Health : NetworkBehaviour {

    public const int MaxHealth = 100;

    [SyncVar]
    public int CurrentHealth = MaxHealth;

    //Only call on server
    void TakeDamage(int damage)
    {
        if (!isServer) return;
        CurrentHealth -= damage;
        if (CurrentHealth < 0)
        {
            CurrentHealth = 0;
        }
        //Destroys object when health hits 0.
        if (CurrentHealth == 0) NetworkServer.Destroy(gameObject);
    }

    [Command]
    public void CmdTakeDamage(int damage)
    {
        TakeDamage(damage);
    }
}
