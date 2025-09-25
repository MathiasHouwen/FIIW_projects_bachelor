using UnityEngine;

public class BlockSpawner : MonoBehaviour
{
    public GameObject blockObjectPrefab;
    public Transform spawnPoint;

    public Transform parentBin;
    public float randomOffset = 0.2f;

    public void SpawnBlock()
    {
        spanw(spawnPoint.position);
    }

    private void spanw(Vector3 location) {
        Vector3 randomOffsetVector = new Vector3(
           Random.Range(-randomOffset, randomOffset),
           0f,
           Random.Range(-randomOffset, randomOffset)
       );
        GameObject block = Instantiate(blockObjectPrefab, location + randomOffsetVector, Quaternion.identity);
        block.transform.SetParent(parentBin);
    }

    public void Spawn30()
    {
        for (float x = 0; x < 5; x++)
        {
            for (float z = 0; z < 3; z++)
            {
                for (float y = 0; y < 2; y++)
                {
                    Vector3 offsetVector = new Vector3(
                        (x - 5 / 2f) * 1.5f,
                        (y - 3 / 2f) * 1.5f,
                        (z - 2 / 2f) * 1.5f
                    );
                    spanw(spawnPoint.position + offsetVector);
                }
            }
        }
    }
}
