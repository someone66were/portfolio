using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;


public class WinScreen : MonoBehaviour
{
    public Image image;
    public TextMeshProUGUI text;
    public float fadeDuration = 1.0f;

    public void Start()
    {
        Color imageColor = image.color;
        imageColor.a = 0;
        image.color = imageColor;

        Color textColor = text.color;
        textColor.a = 0;
        text.color = textColor;
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            StartCoroutine(FadeInUI());
        }
    }

    private IEnumerator FadeInUI()
    {
        // Плавное появление изображения
        yield return StartCoroutine(FadeImage(image, 1, fadeDuration));

        // Плавное появление текста
        yield return StartCoroutine(FadeText(text, 1, fadeDuration));
    }

    private IEnumerator FadeImage(Image image, float targetAlpha, float duration)
    {
        Color startColor = image.color;
        float startAlpha = startColor.a;
        float time = 0;

        while (time < duration)
        {
            time += Time.deltaTime;
            float newAlpha = Mathf.Lerp(startAlpha, targetAlpha, time / duration);
            image.color = new Color(startColor.r, startColor.g, startColor.b, newAlpha);
            yield return null;
        }

        image.color = new Color(startColor.r, startColor.g, startColor.b, targetAlpha); // Убедитесь, что альфа установлена точно в конечное значение
    }

    private IEnumerator FadeText(TextMeshProUGUI text, float targetAlpha, float duration)
    {
        Color startColor = text.color;
        float startAlpha = startColor.a;
        float time = 0;

        while (time < duration)
        {
            time += Time.deltaTime;
            float newAlpha = Mathf.Lerp(startAlpha, targetAlpha, time / duration);
            text.color = new Color(startColor.r, startColor.g, startColor.b, newAlpha);
            yield return null;
        }

        text.color = new Color(startColor.r, startColor.g, startColor.b, targetAlpha); // Убедитесь, что альфа установлена точно в конечное значение
    }
}
