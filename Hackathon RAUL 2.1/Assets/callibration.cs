using UnityEngine;
using System.Collections;

public class callibration : MonoBehaviour {

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKey(KeyCode.UpArrow)) gameObject.transform.Translate((float)0, (float)0, (float)0.0005);
        else if (Input.GetKey(KeyCode.DownArrow)) gameObject.transform.Translate((float)0, (float)0.000, (float)-0.0005);

        if (Input.GetKey(KeyCode.RightArrow)) gameObject.transform.Translate((float)0.0005, (float)0, (float)0);
        else if (Input.GetKey(KeyCode.LeftArrow)) gameObject.transform.Translate((float)-0.0005, (float)0, (float)0);
    }
}
