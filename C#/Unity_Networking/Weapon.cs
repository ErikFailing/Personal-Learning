using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Weapon : MonoBehaviour {

    public int Damage = 35;
    public int CoolDown = 0;
    public List<GameObject> Touching;
    public GameObject WeaponHolder;
    
	void Start ()
    {
        WeaponHolder = gameObject.transform.parent.gameObject;
    }

    private void FixedUpdate()
    {
        if (CoolDown != 0)
        {
            CoolDown -= 1;
            return;
        } 
        int index = 0;
        while (index < Touching.Count)
        {
            if(Touching[index].GetComponent<Health>() != null && Touching[index] != WeaponHolder)
            {
                Touching[index].GetComponent<Health>().CmdTakeDamage(Damage);
                CoolDown = 100;
                return;
            }
            index += 1;
        }
    }

    void OnCollisionEnter2D(Collision2D other)
    {
        Touching.Add(other.gameObject);
    }

    void OnCollisionExit2D(Collision2D other)
    {
        Touching.Remove(other.gameObject);
    }
}
