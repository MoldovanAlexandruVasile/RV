using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cannon : MonoBehaviour {

	public GameObject projectile;
	public float speed = 20;
	public Rigidbody body;


	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if (Input.GetButtonDown("Fire1"))
		{
			GameObject instantiatedProjectile = Instantiate(projectile,
														   transform.position,
														   transform.rotation)
				as GameObject;

			Rigidbody instantiatedProjectile2 = instantiatedProjectile.GetComponent<Rigidbody>();
			instantiatedProjectile2.velocity = transform.TransformDirection(new Vector3(0, 0, speed));

		}
	}
}
