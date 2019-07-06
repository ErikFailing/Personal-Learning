using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour {

    public GameObject cameraFocus;
    private Camera cam;
    private Vector3 offset;
    private int cameraScroll;
    
    // Use this for initialization
	void Start ()
    {
        cam = this.GetComponent<Camera>();
        cameraScroll = 0;
	}
	
	// Update is called once per frame
	void Update ()
    {
        if (cameraFocus == null) return;
        SetCameraScroll();
	}

    void LateUpdate ()
    {
        if (cameraFocus == null) return;
        CameraFollow();
        ScrollCamera();
    }

    //Gets the mousewheel inputs
    void SetCameraScroll ()
    {
        if (Input.GetAxis("Mouse ScrollWheel") > 0) cameraScroll = 1;
        else if (Input.GetAxis("Mouse ScrollWheel") < 0) cameraScroll = -1;
        else cameraScroll = 0;
    }

    //Transforms the camera to follow whatever it is currently focusing on
    void CameraFollow ()
    {
        Vector3 Transform = new Vector3(cameraFocus.transform.position.x, cameraFocus.transform.position.y, -10);
        transform.position = Transform;
    }

    //Scrolls The camera in and out
    void ScrollCamera ()
    {
        if (cameraScroll < 0) cam.orthographicSize += 3;
        else if (cameraScroll > 0) cam.orthographicSize += -3;
    }

    //Sets the focus of the Camera
    public void setFocus(GameObject focus)
    {
        cameraFocus = focus;
    }
}
