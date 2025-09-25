using System.Collections.Generic;
using UnityEngine;

public class Bin : MonoBehaviour
{
    public Collider detectionVolume;

    public void Clear()
    {
        foreach (GameObject block in detectBlocksInside())
        {
            Destroy(block);
        }
    }

    public List<GameObject> detectBlocksInside()
    {
        List<GameObject> blocks = new List<GameObject>();

        foreach (Transform obj in transform)
        {
            if (isInBounds(obj.position) && isBlock(obj.gameObject))
            {
                blocks.Add(obj.gameObject);
            }
        }
        return blocks;
    }

    private bool isInBounds(Vector3 position)
    {
        return detectionVolume.bounds.Contains(position);
    }

    private bool isBlock(GameObject obj)
    {
        return obj.CompareTag("block");
    }
}
