using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class MainController : MonoBehaviour
{
    public Robot robot;
    public Bin sourceBinScript;
    public Transform targetBin;
    public Transform targetGridShape;
    public int gridColumns = 8;
    public int gridRows = 4;

    public void StartTransfer()
    {
        StartCoroutine(TransferBlocks());
    }

    private IEnumerator TransferBlocks()
    {
        List<GameObject> blocks = sourceBinScript.detectBlocksInside();

        for (int i = 0; i < blocks.Count; i++)
        {
            GameObject block = blocks[i];
            Vector3 dropPos = CalculateGridPosition(i);

            bool moveDone = false;
            robot.MoveBlock(block, targetBin, dropPos, () => moveDone = true);
            yield return new WaitUntil(() => moveDone);
        }
    }

    private Vector3 CalculateGridPosition(int index)
{
    int layerSize = gridColumns * gridRows;

    int layer = index / layerSize;
    int layerIndex = index % layerSize;

    int row = layerIndex / gridColumns;
    int col = layerIndex % gridColumns;

    Vector3 basePos = targetGridShape.position;

    float totalWidth = targetGridShape.localScale.x * 10f;
    float totalDepth = targetGridShape.localScale.z * 10f;

    float spacingX = totalWidth / Mathf.Max(gridColumns - 1, 1);
    float spacingZ = totalDepth / Mathf.Max(gridRows - 1, 1);
    float verticalSpacing = 0.75f;

    Vector3 offset = new Vector3(
        col * spacingX - totalWidth / 2f,
        0.4f + layer * verticalSpacing,
        row * spacingZ - totalDepth / 2f
    );

    return basePos + offset;
}


}
