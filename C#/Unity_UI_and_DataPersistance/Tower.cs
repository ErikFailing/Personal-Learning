using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//This class shoot projectiles at valid gameobject types
public class Tower : MonoBehaviour {

    public float fireRate = 1;
    public float projectileOriginOffset = 1;
    public GameObject projectile;
    public bool dynamicTargetingOnly = true;
    public Collider2D Range;

    public Collider2D[] possibleTargets = new Collider2D[1000];
    public List<Transform> validTargets = new List<Transform>();
    public Transform target;
    private int framesSinceLastShot = 0;
    private int layerMaskLineOfSight; // 0000 0000 0000 0000     0101 1000 0000 0000  OR  22528
    private int layerMaskTargets; // 0000 0000 0000 0000     0101 0000 0000 0000  OR  20480
    private Transform projectilesParent;
    private ContactFilter2D con =  new ContactFilter2D();

    private void Start()
    {
        //Create the layermasks
        layerMaskLineOfSight = 22528;
        layerMaskTargets = 20480;

        //Get the child transform to store projectiles fired under
        projectilesParent = transform.Find("Projectiles");
        
        //Create the contact filter
        con.SetLayerMask(layerMaskTargets);
        con.useTriggers = false;
    }

    private void FixedUpdate()
    {
        //Clear the possible targets array
        possibleTargets = new Collider2D[1000];

        //Get objects with colliders in range
        Physics2D.OverlapCollider(Range, con, possibleTargets);

        //Increment framesSinceLastShot by one up to a maximum of 5000 or '100 seconds'
        if (framesSinceLastShot < 5000) framesSinceLastShot += 1;

        //If there are no possible targets, return
        if (possibleTargets == null) return;

        //Reset what targets are valid
        validTargets = new List<Transform>();

        //Next test each possible target to see if the tower can target it
        foreach (Collider2D go in possibleTargets)
        {
            //If out of colliders to check, break
            if (go == null) break;
            
            //If possible target does not have the "Tags" script, continue
            if (!go.gameObject.GetComponent<Tags>()) continue;
            
            //If tower only targets dynamic rigidbodies and this possible target is NOT dynamic, continue
            if (dynamicTargetingOnly && go.gameObject.GetComponent<Rigidbody2D>().bodyType != RigidbodyType2D.Dynamic) continue;

            //If possible target's faction matches the tower's faction, continue
            if (GetComponent<Tags>().faction == go.gameObject.GetComponent<Tags>().faction) continue;

            //Cast a ray towards the possible target, if it does not hit the target, continue
            Vector2 directionRaycast = new Vector2(go.transform.position.x - transform.position.x, go.transform.position.y - transform.position.y);
            Vector2 originRaycast = Vector2.MoveTowards(transform.position, go.transform.position, projectileOriginOffset);
            float distance = Vector2.Distance(go.transform.position, transform.position);
            RaycastHit2D lineOfSight = Physics2D.Raycast(originRaycast , directionRaycast,  distance + 100, layerMaskLineOfSight); //Need to create an appropiate layermask, ignore projectiles
            if (go.transform != lineOfSight.transform) continue;

            //Finally Add possible target to valid target array
            validTargets.Add(go.transform);
        }

        //If no vaild targets, return
        if (validTargets.Count == 0) return;

        //Decide what valid target the tower should shoot based on its selection settings
        target = validTargets[0];
        foreach (Transform go in validTargets)
        {
            //if go is closer to the tower than target, target = go
            if (Vector2.Distance(go.position, transform.position) < Vector2.Distance(target.position, transform.position)) target = go;
        }

        //If the tower has waited sufficient frames, shoot at the target
        if (framesSinceLastShot >= fireRate * 50)
        {
            Vector2 originProjectile = Vector2.MoveTowards(transform.position, target.position, projectileOriginOffset);
            float angle = Vector2.SignedAngle(new Vector3(0, 100, 0), target.position - transform.position);
            Instantiate(projectile, originProjectile, Quaternion.Euler(0, 0, angle), projectilesParent);
            framesSinceLastShot = 0;
        }
    }


}