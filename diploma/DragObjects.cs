using UnityEngine;

public class DragObjects : MonoBehaviour
{
    private bool isDragging = false;
    private Vector3 offset;
    public Transform correctPosition;
    public float placementThreshold = 0.5f;
    public bool isPlacedCorrectly = false;

    void OnMouseDown()
    {
        if (!isPlacedCorrectly)
        {
            isDragging = true;
            offset = transform.position - GetMouseWorldPos();
        }
    }

    void OnMouseUp()
    {
        if (!isPlacedCorrectly)
        {
            isDragging = false;
            CheckPlacement();
        }
    }

    void Update()
    {
        if (!isPlacedCorrectly)
        {
            if (isDragging)
            {
                Vector3 mousePos = GetMouseWorldPos() + offset;
                transform.position = new Vector3(mousePos.x, transform.position.y, mousePos.z);
            }
        }
    }

    Vector3 GetMouseWorldPos()
    {
        Vector3 mousePoint = Input.mousePosition;
        mousePoint.z = Camera.main.WorldToScreenPoint(gameObject.transform.position).z;
        return Camera.main.ScreenToWorldPoint(mousePoint);
    }

    public void CheckPlacement()
    {
        if (Vector3.Distance(transform.position, correctPosition.position) <= placementThreshold)
        {
            transform.position = correctPosition.position;
            Debug.Log("Correct placement!");
            isPlacedCorrectly = true;
            // Дополнительные действия при правильном размещении
        }
        else
        {
            Debug.Log("Incorrect placement.");
            isPlacedCorrectly = false;
            // Дополнительные действия при неправильном размещении
        }
    }
}