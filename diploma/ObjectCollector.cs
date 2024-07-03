using UnityEngine;
using UnityEngine.UI;

public class ObjectCollector : MonoBehaviour
{
    [System.Serializable]
    public struct Collectible
    {
        public GameObject collectibleObject;
        public GameObject tableObject;
    }

    public Collectible[] collectibles;
    public float raycastDistance = 5.0f;
    public KeyCode collectKey = KeyCode.E;
    public GameObject canvas;

    private void Start()
    {
        canvas.gameObject.SetActive(false);
    }

    void Update()
    {
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit, raycastDistance))
        {
            for (int i = 0; i < collectibles.Length; i++)
            {
                if (hit.collider.gameObject == collectibles[i].collectibleObject)
                {
                    // �������� ������� Canvas
                    canvas.gameObject.SetActive(true);

                    if (Input.GetKeyDown(collectKey))
                    {
                        // �������������� ��������� ������
                        collectibles[i].collectibleObject.SetActive(false);
                        // ������������ ��������������� ������ �� �����
                        collectibles[i].tableObject.SetActive(true);
                        // ������ ������� Canvas
                        canvas.gameObject.SetActive(false);
                    }

                    return;
                }
            }
        }

        // ������ ������� Canvas, ���� �� ������� �� ������
        canvas.gameObject.SetActive(false);
    }
}
