using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;

public class RefreshGraph : MonoBehaviour {

    //Updates entire graph, too laggy
    /*
    public float graphUpdateRate = 1;

    private int timer = 0;

    private void FixedUpdate()
    {
        if (timer < 10000) timer += 1;

        if (timer < graphUpdateRate * 50) return;

        AstarPath.active.Scan(AstarPath.active.data.gridGraph);
        timer = 0;
    }
    */

    private void FixedUpdate()
    {
        Bounds bounds = GetComponent<Collider2D>().bounds;
        var guo = new GraphUpdateObject(bounds);

        guo.updatePhysics = true;
        AstarPath.active.UpdateGraphs(guo);
    }

}
