using UnityEngine;
using UnityEngine.UI;

public class NoteCollector : MonoBehaviour
{
    private bool isLookingAtNote = false;
    private bool isReadingNote = false;

    public GameObject readText; 
    public GameObject noteImage;
    public GameObject noteBackground;
    public GameObject charge;

    private FirstPersonController playerController;
    private Shooting playerShooting;

    void Start()
    {
        readText.SetActive(false);
        noteImage.SetActive(false);
        noteBackground.SetActive(false);

        playerController = FindObjectOfType<FirstPersonController>();
        playerShooting = FindObjectOfType<Shooting>();
    }

    void Update()
    {
        if (isLookingAtNote && Input.GetKeyDown(KeyCode.E))
        {
            if (!isReadingNote)
            {
                ReadNote();
            }
            else
            {
                CloseNote();
            }
        }
    }

    private void ReadNote()
    {
        isReadingNote = true;
        noteImage.SetActive(true);
        noteBackground.SetActive(true);
        charge.SetActive(false);
        readText.SetActive(false);

        // Отключаем движения и стрельбу игрока
        playerController.enabled = false;
        playerShooting.enabled = false;

        // Останавливаем время
        Time.timeScale = 0;
    }

    private void CloseNote()
    {
        isReadingNote = false;
        noteImage.SetActive(false);
        noteBackground.SetActive(false);
        charge.SetActive(true);
        readText.SetActive(true);

        // Включаем движения и стрельбу игрока
        playerController.enabled = true;
        playerShooting.enabled = true;

        // Возобновляем время
        Time.timeScale = 1;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            isLookingAtNote = true;
            readText.SetActive(true);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            isLookingAtNote = false;
            readText.SetActive(false);
        }
    }
}
