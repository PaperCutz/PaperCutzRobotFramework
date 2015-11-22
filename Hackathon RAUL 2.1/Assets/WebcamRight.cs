using UnityEngine;
using System.Collections;

public class WebcamRight : MonoBehaviour
{
    WebCamTexture tex;
    Texture2D preview;
    Renderer renderer;
    // Use this for initialization
    void Start()
    {
        WebCamDevice[] devices = WebCamTexture.devices;
        for (var i = 0; i < devices.Length; i++)
            print(devices[i].name);
        tex = new WebCamTexture("USB_Camera");
        print("This device: " + tex.deviceName);
        renderer = GetComponent<Renderer>();
        tex.Play();
        preview = new Texture2D(tex.width, tex.height);
    }

    // Update is called once per frame
    void Update()
    {
        preview.SetPixels(tex.GetPixels());
        preview.Apply();
        renderer.material.mainTexture = preview;

    }
}
