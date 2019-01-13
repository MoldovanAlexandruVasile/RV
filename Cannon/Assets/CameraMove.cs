using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMove : MonoBehaviour {
	public float Sensitivity;

	// Use this for initialization
	void Start () {
		Cursor.visible = false;
	}
	
	// Update is called once per frame
	void Update () {
		float newRotationY = transform.localEulerAngles.y + Input.GetAxis("Mouse X") * Sensitivity;
		float newRotationX = transform.localEulerAngles.x + Input.GetAxis("Mouse Y") * Sensitivity;
		gameObject.transform.localEulerAngles = new Vector3(newRotationX, newRotationY, 0);
	}
}
