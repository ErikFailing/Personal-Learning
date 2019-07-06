using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    public GameObject target;

    private float MAX_SIZE = 25;
    private float MIN_SIZE = .25f;
    private float cameraSize;

    void Start()
    {
        cameraSize = GetComponent<Camera>().orthographicSize;
    }

    // Update is called once per frame
    void Update()
    {
        gameObject.transform.position = new Vector3(target.transform.position.x, target.transform.position.y, -10);

        cameraSize -=  2 * Input.GetAxis("Mouse ScrollWheel");
        if (cameraSize > MAX_SIZE) cameraSize = MAX_SIZE;
        else if (cameraSize < MIN_SIZE) cameraSize = MIN_SIZE;
        ChangeCameraSize(cameraSize);
    }

    void ChangeCameraSize(float size)
    {
        GetComponent<Camera>().orthographicSize = size;
        transform.Find("Light").GetComponent<Camera>().orthographicSize = size;
    }

}
