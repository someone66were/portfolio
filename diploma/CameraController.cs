using UnityEngine;
using System.Collections;

public class CameraController : MonoBehaviour
{
    [SerializeField] private Transform overheadPosition;
    [SerializeField] private Transform player;
    [SerializeField] private GameObject playerobj;
    [SerializeField] private GameObject camObj;

    private bool isCameraOverhead = false;
    private float transitionSpeed = 1.0f; 
    private Quaternion startRot;

    public GameObject interact;

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.E))
        {
            if (!isCameraOverhead)
            {
                startRot = camObj.transform.rotation;
                StartCoroutine(MoveCameraOverhead());
            }
            else
            {
                StartCoroutine(MoveCameraBack());
            }
        }
    }

    IEnumerator MoveCameraOverhead()
    {
        isCameraOverhead = true;
        float t = 0.0f;
        Vector3 startingPos = transform.position;
        Quaternion startingRot = transform.rotation;
        playerobj.GetComponent<FirstPersonController>().enabled = false;
        //playerobj.GetComponent<Shooting>().enabled = false;
        interact.SetActive(false);

        while (t < 1.0f)
        {
            t += Time.deltaTime * transitionSpeed;
            transform.position = Vector3.Lerp(startingPos, overheadPosition.position, t);
            transform.rotation = Quaternion.Lerp(startingRot, overheadPosition.rotation, t);
            yield return null;
        }
        Cursor.lockState = CursorLockMode.None;
    }

   public IEnumerator MoveCameraBack()
    {
        isCameraOverhead = false;
        float t = 0.0f;
        Vector3 newStartingPos = transform.position;
        Quaternion newStartingRot = transform.rotation;
        Cursor.lockState = CursorLockMode.Locked;

        while (t < 1.0f)
        {
            t += Time.deltaTime * transitionSpeed;
            transform.position = Vector3.Lerp(newStartingPos, player.position, t);
            transform.rotation = Quaternion.Lerp(newStartingRot, startRot, t);
            yield return null;
        }
        playerobj.GetComponent<FirstPersonController>().enabled = true;
       // playerobj.GetComponent<Shooting>().enabled = true;
        interact.SetActive(true);
    }
}
