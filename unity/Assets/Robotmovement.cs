using UnityEngine;

public class RobotMovement : MonoBehaviour
{
    public Robot robot;
    public float moveSpeed = 2f;
    public float verticalBeamLength = 1.0f;
    private enum MovePhase { None, MoveUp, MoveXZ, MoveDown }
    private MovePhase currentPhase = MovePhase.None;
    public System.Action OnMovementComplete; // ✅ Callback here
    private Vector3? fullTarget = null; // Final target for the tip
    private Vector3 horizontalBeamPos;
    private Vector3 verticalBeamPos;

    void Start()
    {
        if (robot == null)
        {
            Debug.LogError("Robot not assigned.");
            return;
        }

        horizontalBeamPos = robot.horizontalBeam.localPosition;
        verticalBeamPos = robot.verticalBeam.localPosition;
    }

    void Update()
    {
        if (fullTarget.HasValue)
        {
            HandleMovement();
        }
    }

    public void MoveTipTo(Vector3 target)
    {
        fullTarget = target;
        currentPhase = MovePhase.MoveUp;
    }

    private void HandleMovement()
    {
        Vector3 currentTip = robot.verticalBeam.localPosition;
        currentTip.y -= verticalBeamLength;

        float step = moveSpeed * Time.deltaTime;
        Vector3 target = fullTarget.Value;

        switch (currentPhase)
        {
            case MovePhase.MoveUp:
                float targetY = robot.horizontalBeam.localPosition.y; // height of horizontal beam
                if (Mathf.Abs(currentTip.y - targetY) > 0.01f)
                {
                    MoveTipVertically(targetY, step);
                }
                else
                {
                    currentPhase = MovePhase.MoveXZ;
                }
                break;

            case MovePhase.MoveXZ:
                Vector2 currentXZ = new Vector2(currentTip.x, currentTip.z);
                Vector2 targetXZ = new Vector2(target.x, target.z);

                if ((currentXZ - targetXZ).magnitude > 0.01f)
                {
                    MoveTipXZ(targetXZ, step);
                }
                else
                {
                    currentPhase = MovePhase.MoveDown;
                }
                break;

            case MovePhase.MoveDown:
                if (Mathf.Abs(currentTip.y - target.y) > 0.01f)
                {
                    MoveTipVertically(target.y, step);
                }
                else
                {
                    currentPhase = MovePhase.None;
                    fullTarget = null;

                    OnMovementComplete?.Invoke(); // ✅ Callback trigger
                }
                break;
        }
    }

    private void MoveTipVertically(float targetTipY, float step)
    {
        Vector3 current = robot.verticalBeam.localPosition;
        float currentTipY = current.y - verticalBeamLength;
        float newTipY = Mathf.MoveTowards(currentTipY, targetTipY, step);
        current.y = newTipY + verticalBeamLength;
        robot.verticalBeam.localPosition = current;
    }

    private void MoveTipXZ(Vector2 targetXZ, float step)
    {
        Vector3 hPos = robot.horizontalBeam.localPosition;
        Vector3 vPos = robot.verticalBeam.localPosition;

        Vector3 tip = vPos;
        tip.y -= verticalBeamLength;

        float newX = Mathf.MoveTowards(tip.x, targetXZ.x, step);
        float newZ = Mathf.MoveTowards(tip.z, targetXZ.y, step);

        float deltaX = newX - tip.x;
        float deltaZ = newZ - tip.z;

        vPos.x += deltaX;
        vPos.z += deltaZ;
        hPos.z += deltaZ;

        robot.verticalBeam.localPosition = vPos;
        robot.horizontalBeam.localPosition = hPos;
    }
}
