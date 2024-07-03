using UnityEngine;
using UnityEngine.UI;

public class TriggerZone : MonoBehaviour
{
    [SerializeField]private CameraController cameraController; // ������ �� ������ CameraController
    public GameObject interact;

    void Start()
    {
        if (interact != null)
        {
            interact.SetActive(false); // �������� ����� �� ���������
        }
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player")) // ��������, ��� � ������� ������ �����
        {
            cameraController.enabled = true; // �������� ������ CameraController
            interact.SetActive(true);
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player")) // ��������, ��� �� �������� ������� �����
        {
            cameraController.enabled = false; // ��������� ������ CameraController
            interact.SetActive(false);
        }
    }

   public void DestroyZone()
    {
        interact.SetActive(false);
        Destroy(this.gameObject);
    }

    public void Delay()
    {
        cameraController.enabled = false;
        Invoke("DestroyZone", 1.5f);
    }
}
