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
                    // Показать элемент Canvas
                    canvas.gameObject.SetActive(true);

                    if (Input.GetKeyDown(collectKey))
                    {
                        // Деактивировать собранный объект
                        collectibles[i].collectibleObject.SetActive(false);
                        // Активировать соответствующий объект на столе
                        collectibles[i].tableObject.SetActive(true);
                        // Скрыть элемент Canvas
                        canvas.gameObject.SetActive(false);
                    }

                    return;
                }
            }
        }

        // Скрыть элемент Canvas, если не смотрит на объект
        canvas.gameObject.SetActive(false);
    }
}
