using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//This method the gameobject it is attached to pulse in size
public class LightPulse : MonoBehaviour {
    
    public float pulseChangeRate = .001f;
    public float pulseMaxSize = .1f;
    
    public bool growing = true;
    public float baseSize;

    //Get the initial size of the light
    private void Start()
    {
        baseSize = transform.localScale.x;
    }

    private void FixedUpdate()
    {
        //Switch state of the light size
        if (transform.localScale.x <= baseSize + pulseMaxSize) growing = false;
        if (transform.localScale.x >= baseSize - pulseMaxSize) growing = true;
        //Grow or shrink the light
        if (growing == true) transform.localScale.Set(transform.localScale.x + pulseChangeRate, transform.localScale.y + pulseChangeRate, 1);
        else transform.localScale.Set(transform.localScale.x - pulseChangeRate, transform.localScale.y - pulseChangeRate, 1);
    }

}
