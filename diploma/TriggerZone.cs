using UnityEngine;
using UnityEngine.UI;

public class TriggerZone : MonoBehaviour
{
    [SerializeField]private CameraController cameraController; // Ссылка на скрипт CameraController
    public GameObject interact;

    void Start()
    {
        if (interact != null)
        {
            interact.SetActive(false); // Скрываем текст по умолчанию
        }
    }

    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player")) // Проверка, что в триггер входит игрок
        {
            cameraController.enabled = true; // Включаем скрипт CameraController
            interact.SetActive(true);
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player")) // Проверка, что из триггера выходит игрок
        {
            cameraController.enabled = false; // Выключаем скрипт CameraController
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
